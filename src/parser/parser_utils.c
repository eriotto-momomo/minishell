/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 18:55:44 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast	*ast_new_node(t_ast cmd)
{
	t_ast	*ptr;

	// ptr = malloc(sizeof(t_ast));
	w_malloc((void **)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = cmd;
	return (ptr);
}

void	consume_token(t_list **head)
{
	if ((*head)->data)
	{
		free((*head)->data);
		(*head)->data = NULL;
		// printf("consume_token | %sfree((*head)->data)%s\n", C, RST);	// 💥DEBUGING
	}
	if ((*head)->next)
	{
		*head = (*head)->next;
		// Différence entr ça et: `head = &(*head)->next;` ?
		// printf("&& %shead = (*head)->next%s\n", C, RST);				// 💥DEBUGING
	}
}


/*	FIRST VERSION BACKUP
	while ((*head)->data && ((*head)->data[0] != '|' || (*head)->data[0] != ')'
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
	}
*/
void	fill_exec_node(t_list **head, t_ast *cmd, int *argc)
{
	while ((*head)->data && ((*head)->data[0] != '|' || (*head)->data[0] != ')'
		|| (*head)->data[0] != '&' || (*head)->data[0] != ';'))
	{
		if ((*head)->type != WORD)
			break;
		cmd->data.ast_exec.argv[(*argc)] = ft_strdup((*head)->data);
		if (!cmd->data.ast_exec.argv[(*argc)])
		{
			errno = ENOMEM;
			ft_puterror("parse_exec", strerror(errno));
			exit(1); // ❔
		}
		consume_token(head);
		(*argc)++;
		if (*argc >= 10) 				// 🗯️ À voir le nombre d'args max à gérer ❔
		{
			ft_puterror("parse_exec", "too many args");
			exit(1);					// 💥TEST
		}
	}
	print_exec_args(cmd->data.ast_exec.argv);	// 🖨️PRINT💥DEBUGING

}

void	print_exec_args(char **node)
{
	int	i;

	i = 0;
	while (node[i] && node[i][0])
	{
		printf("print_exec_args ");
		printf("[%s%s%s] ", C, node[i], RST); // 💥DEBUGING
		printf("\n");
		i++;
	}
}

void	print_ast(t_ast *ast)
{
	t_ast *left;
	t_ast *right;
	t_ast *redir;
	if (ast->tag == AST_PIPE)
	{
		left = ast->data.ast_pipe.left;
		right = ast->data.ast_pipe.right;
		if (left->tag == AST_EXEC)
		{
			//printf("print_ast  | L. BRANCH: [%sAST_EXEC%s  node]\n", P, RST);
			printf("print_ast  | L. BRANCH:");
			for (int i = 0; i < left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("print_ast  | L. BRANCH: [%sAST_EXEC%s  node]\n", P, RST);
		else if (left->tag == AST_REDIR)
			printf("print_ast  | L. BRANCH: [%sAST_REDIR%s node]\n", P, RST);
		if (right->tag == AST_EXEC)
		{
			printf("print_ast  | R. BRANCH:");
			for (int i = 0; i < right->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, right->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (right->tag == AST_PIPE)
			printf("print_ast  | R. BRANCH: [%sAST_EXEC%s  node]\n", P, RST);
		else if (right->tag == AST_REDIR)
			printf("print_ast  | R. BRANCH: [%sAST_REDIR%s node]\n", P, RST);
		else
			printf("[%sEMPTY BRANCH%s]\n", B, RST);
	}
	else if (ast->tag == AST_REDIR)
	{
		left = ast->data.ast_redir.left;
		redir = ast;
		if (left->tag == AST_EXEC)
			printf("print_ast  | L. BRANCH: [%sAST_EXEC%s  node]\n", P, RST);
		else if (left->tag == AST_PIPE)
			printf("print_ast  | L. BRANCH: [%sAST_EXEC%s  node]\n", P, RST);
		else if (left->tag == AST_REDIR)
			printf("print_ast  | L. BRANCH: [%sAST_REDIR%s node]\n", P, RST);
		if (redir->data.ast_redir.filename)
			printf("print_ast  | R. BRANCH: filename [%s%s%s] >> mode [%s%d%s]\n", P, redir->data.ast_redir.filename, RST, P, redir->data.ast_redir.mode, RST);
		//else
		//	printf("[%sEMPTY BRANCH%s]\n", B, RST);
	}
	/*else if (ast->tag == AST_BLOCK)
	{
	}*/
}
