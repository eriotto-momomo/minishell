/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/20 22:07:41 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// `PARSING FUNCTIONS` pour analyser la syntaxe
// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

/*
 - WORD =	0
 - PIPE =	1
 - REDIR =	2
*/

// parse_block: (LINE) REDIR
t_ast	*parse_block(t_list **head)
{
	t_ast *cmd;

	if ((*head)->data && (*head)->data[0] != '(')
	{
		ft_puterror("parse_block", "unexpected syntax");
		exit(1);
	}
	cmd = parse_line(head);
	/*if (!get_closing_parenthesis(head)) //						- TO DO👷‍♂️
	{
		ft_puterror("parse_block", "syntax - missing ')'");
		exit(1);
	}*/
	if ((*head)->type == 2) // REDIR
	{
		// CONSOMMATION DU TOKEN
		cmd = parse_redir(head, cmd);
	}

	// ... - TO DO👷‍♂️
	return (cmd);
}

// parse_pipe: EXEC [|PIPE]
t_ast	*parse_pipe(t_list **head)
{
	t_ast *cmd;

	cmd = parse_exec(head);
	if ((*head)->type == 1) // PIPE
	{
		// CONSOMMATION DU TOKEN
		if ((*head)->next)
			*head = (*head)->next;
		cmd = pipe_cmd(cmd, parse_pipe(head));
	}

	// ... - TO DO👷‍♂️
	return (cmd);
}

// parse_line: PIPE {&} [;LINE]
t_ast	*parse_line(t_list **head)
{
	t_ast *cmd;

	/*cmd = NULL;
	if ((*head)->type == 1) // PIPE
	{
		// CONSOMMATION DU TOKEN
		cmd = pipe_cmd(cmd, parse_pipe(head));
	}*/
	printf(">> %sCURRENT TOKEN%s: [%s] | type: %d | next: %p\n", C, RST, (*head)->data, (*head)->type, (void *)(*head)->next);
	cmd = parse_pipe(head);

	// ... - TO DO👷‍♂️
	return (cmd);
}

// parse_redir: {< file}, {> file} ou {>> file}
t_ast	*parse_redir(t_list **head, t_ast *cmd)
{
	if ((*head)->next->type != 0) // WORD
	{
		ft_puterror("parse_redir", "syntax - missing file name");
		exit(1);
	}
	if ((*head)->data && (*head)->data[0] == '<')
	{
		// CONSOMMATION DU TOKEN
		cmd = redir_cmd(cmd, (*head)->next->data, 1, 0);
	}
	else if ((*head)->data && (*head)->data[0] == '>')
	{
		// CONSOMMATION DU TOKEN
		cmd = redir_cmd(cmd, (*head)->next->data, 2, 1);
	}
	else if ((*head)->data && ((*head)->data[0] == '>' && (*head)->data[1] == '>'))
	{
		// CONSOMMATION DU TOKEN
		cmd = redir_cmd(cmd, (*head)->next->data, 3, 1);
	}
	return (cmd);
}

/* Selon: 'Shell Code-- More Detail' @36:36 https://www.youtube.com/watch?v=ZjzMdsTWF0U&list=LL&index=2
/!\ Il n'utilise pas une liste chainée
struct *parseexec(char **ps, char*es)
{
	char *q, *eq;
	int tok, argc;
	struct execcmd *cmd;
	struct cmd *ret; // pointe sur l'AST construit jusqu'à présent

	if(peek(ps, es, "("))
		return parseblock(ps, es);
	ret = execcmd(); // alloue un 'exec node' (blank)
	cmd = (struct execcmd*)ret; // pointeur sur ce 'exec node'
	argc = 0;
	ret = parseredirs(ret, ps, es); *//* /!\ pointe sur une redirection:
	- Au début de parseexec, 'ret' pointait sur l'AST construit jusqu'à présent
	- À présent il pointe sur la redirection qui pointe sur "l'ancien pointeur"
	- En d'autres termes: 'ret' pointe désormais sur l'exec_node qui doit être redirigé
	*//*
	while(!peek(ps, es, "|)&;")) {
		if ((tok=gettoken(ps, es, &q, &eq)) == 0)
			break;
		if (tok != 'a')
			panic("syntax");
		cmd->argv[argc] = q; // 'q' pointe au début du file_name et 'eq' à la fin
		cmd->eargv[argc] = eq; // inutile pour nous... remplir exec_node avec les 'tokens' arguments
		argc++;
		if (argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}
*/

// parse_exec: REDIR {aaa REDIR} ou ( BLOCK
t_ast	*parse_exec(t_list **head)
{
	t_ast	*ret; // Pointe sur l'AST construit jusqu'à présent
	t_ast	*cmd;
	int		argc;

	if ((*head)->data && (*head)->data[0] == '(')
		return (parse_block(head));
	ret = exec_cmd();					// alloue un 'exec_node' (blank)	- ⚠️MALLOC ICI⚠️
	cmd = (t_ast *)ret;					// pointeur sur cet 'exec_node'
	// ret = parse_redir(head, ret);	// gérer les redirections			- TO DO👷‍♂️
	argc = 0;
	while ((*head)->data && ((*head)->data[0] == '|' || (*head)->data[0] == ')'
		|| (*head)->data[0] == '&' || (*head)->data[0] == ';'))
	{
		if ((*head)->type != 0)
		{
			ft_puterror("parse_exec", "syntax");
			exit(1);					// 💥TEST
		}
		cmd->data.ast_exec.argv[argc] = ft_strdup((*head)->data);
		argc++;
		if (argc >= 10) 					// À voir le nombre d'args max à gérer
			ft_puterror("parse_exec", "too many args");
		// ret = parse_redir(head, ret);	// gérer les redirections		- TO DO👷‍♂️
	}
	cmd->data.ast_exec.argc = argc;
	cmd->data.ast_exec.argv[argc] = 0;
	return (0);							// 💥TEST
	//return (ret);						// gérer les redirections			- TO DO👷‍♂️
}
