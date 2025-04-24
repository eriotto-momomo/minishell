/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 16:39:24 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// `PARSING FUNCTIONS` pour analyser la syntaxe
// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

// 🖨️PRINTF de 💥DEBUGING:
//printf(">> %sCURRENT TOKEN%s: [%s%s%s] | type: %d | next: %p\n", C, RST, C, (*head)->data, RST, (*head)->type, (void *)(*head)->next);	// 🖨️PRINT💥DEBUGING
//printf("%sparse_exec%s | while-loop %sSTART%s\n", Y, RST, G, RST);			// 💥DEBUGING
//printf("%sparse_exec%s | while-loop %sEND%s\n", Y, RST, R, RST);		// 💥DEBUGING

//	head->types:
//	WORD =	0
//	IN_REDIR = 1
//	OUT_REDIR = 2
//	APP_OUT_REDIR = 3
//	HERE_DOC = 4
//	PIPE = 5

// parse_block: (LINE) REDIR
t_ast	*parse_block(t_list **head)
{
	t_ast *cmd;

	if ((*head)->data && (*head)->data[0] != '(')
	{
		ft_puterror("parse_block", "unexpected syntax");
		exit(1); // ❔
	}
	cmd = parse_line(head);
	/*if (!get_closing_parenthesis(head)) //						- TO DO👷‍♂️
	{
		ft_puterror("parse_block", "syntax - missing ')'");
		exit(1);
	}*/
	if ((*head)->type == IN_REDIR || (*head)->type == OUT_REDIR
		|| (*head)->type == APP_OUT_REDIR || (*head)->type == HERE_DOC)
		cmd = parse_redir(head, cmd);

	// ... - TO DO👷‍♂️
	return (cmd);
}

// parse_pipe: EXEC [|PIPE]
t_ast	*parse_pipe(t_list **head)
{
	t_ast *cmd;

	cmd = parse_exec(head);
	print_ast(cmd);			// 🖨️PRINT💥DEBUGING
	if ((*head)->type == PIPE)
	{
		consume_token(head);
		cmd = pipe_cmd(cmd, parse_pipe(head));
		print_ast(cmd); 	// 🖨️PRINT💥DEBUGING
	}
	return (cmd);
}


// parse_line: PIPE {&} [;LINE]
t_ast	*parse_line(t_list **head)
{
	t_ast *cmd;

	cmd = parse_pipe(head);
	//if ((*head)->data && ((*head)->data[0] == '&' || (*head)->data[0] == ';'))	// Demandé dans le sujet❔

	// ... - TO DO👷‍♂️
	return (cmd);
}

// '<':		fd = 0, O_RDONLY						-> mode = 1 (redir input)(reading)
// '>':		fd = 1, O_WRONLY | O_CREATE | O_TRUNC	-> mode = 2 (redir output)(creating / overwriting)
// '>>':	fd = 1, O_WRONLY | O_CREATE				-> mode = 3 (redir output)(appending)
// '<<':	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
// ⚠️ `*cmd` pointe sur la branche gauche
// parse_redir: {< file}, {> file} ou {>> file}
t_ast	*parse_redir(t_list **head, t_ast *cmd)
{
	if ((*head)->type != IN_REDIR && (*head)->type != OUT_REDIR
		&& (*head)->type != APP_OUT_REDIR && (*head)->type != HERE_DOC)
		return (cmd);
	else if ((*head)->type == IN_REDIR || (*head)->type == OUT_REDIR
		|| (*head)->type == APP_OUT_REDIR || (*head)->type == HERE_DOC)
	{						// 🖨️PRINT💥DEBUGING
		if ((*head)->type == IN_REDIR)
			cmd = redir_cmd(cmd, (*head)->next->data, 1);
		else if ((*head)->type == OUT_REDIR)
			cmd = redir_cmd(cmd, (*head)->next->data, 2);
		else if ((*head)->type == APP_OUT_REDIR)
			cmd = redir_cmd(cmd, (*head)->next->data, 3);
		else if ((*head)->type == HERE_DOC)
			cmd = redir_cmd(cmd, (*head)->next->data, 4);
		//print_ast(cmd); 	// 🖨️PRINT💥DEBUGING
	}						// 🖨️PRINT💥DEBUGING
	consume_token(head);
	return (cmd);
}

// parse_exec: REDIR {aaa REDIR} ou ( BLOCK
t_ast	*parse_exec(t_list **head)
{
	t_ast	*ret; 						// Pointe sur l'AST construit jusqu'à présent
	t_ast	*cmd;
	int		argc;

	if ((*head)->data && (*head)->data[0] == '(')
		return (parse_block(head));		// exec dans un `subshell`			- TO DO👷‍♂️
	ret = exec_cmd();					// alloue un 'exec_node' (blank)	- ⚠️MALLOC ICI⚠️
	cmd = (t_ast *)ret;					// pointeur sur cet 'exec_node'
	ret = parse_redir(head, ret);		// ⚠️ `ret` pointe sur la branche gauche d'une eventuelle REDIR
	argc = 0;
	/*while ((*head)->data && ((*head)->data[0] != '|' || (*head)->data[0] != ')'
		|| (*head)->data[0] != '&' || (*head)->data[0] != ';'))
	{
		if ((*head)->type != WORD)
			break;
		cmd->data.ast_exec.argv[argc] = ft_strdup((*head)->data);
		if (!cmd->data.ast_exec.argv[argc])
		{
			errno = ENOMEM;
			ft_puterror("parse_exec", strerror(errno));
			exit(1); // ❔
		}
		consume_token(head);
		argc++;
		if (argc >= 10) 				// 🗯️ À voir le nombre d'args max à gérer ❔
		{
			ft_puterror("parse_exec", "too many args");
			exit(1);					// 💥TEST
		}
		ret = parse_redir(head, ret);			// 🗯️ 1st ver.: n'est jamais check si (*head)->type != WORD) ❔
	}*/
	fill_exec_node(head, cmd, &argc);	// 💥TEST
	print_exec_args(cmd->data.ast_exec.argv);	// 🖨️PRINT💥DEBUGING
	printf(">> %sCURRENT TOKEN%s: [%s%s%s] | type: %d | next: %p\n", C, RST, C, (*head)->data, RST, (*head)->type, (void *)(*head)->next);	// 🖨️PRINT💥DEBUGING
	if ((*head)->data && ((*head)->type == IN_REDIR || (*head)->type == OUT_REDIR
		|| (*head)->type == APP_OUT_REDIR || (*head)->type == HERE_DOC))
	{
		printf("%sparse_exec%s | %sREDIR detected!%s\n", Y, RST, B, RST);		// 💥DEBUGING
		ret = parse_redir(head, ret);			// 🗯️ 2nd ver.: si il y' a encore de la data check si REDIR ❔
	}
	cmd->data.ast_exec.argc = argc;
	cmd->data.ast_exec.argv[argc] = ft_strdup("");
	return (ret);
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
