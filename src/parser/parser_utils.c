/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/25 22:26:38 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	consume_token(t_list **head)
{
	if ((*head)->data)
	{
		free((*head)->data);
		(*head)->data = NULL;
	}
	if ((*head)->next)
	{
		*head = (*head)->next;
	}
}

void	fill_exec_node(t_list **head, t_ast *cmd, int *argc)
{
	while ((*head)->data && ((*head)->data[0] != '|' || (*head)->data[0] != ')'
		|| (*head)->data[0] != '&' || (*head)->data[0] != ';'))
	{
		if ((*head)->type != WORD)
			break;
		if ((*head)->data[0] == '\"' || (*head)->data[0] == '\'')
			cmd->data.ast_exec.argv[(*argc)] = ft_strtrim((*head)->data, "\'\"");
		else
			cmd->data.ast_exec.argv[(*argc)] = ft_strdup((*head)->data);
		if (!cmd->data.ast_exec.argv[(*argc)])
		{
			errno = ENOMEM;
			ft_puterror("parse_exec", strerror(errno));
			exit(1); // 🗯️ Ou on "catch" errno dans le main pour quit clean ❔
		}
		consume_token(head);
		(*argc)++;
		if (*argc >= 10)	// 🗯️ Nombre d'args max à gérer ❔
		{
			ft_puterror("parse_exec", "too many args");
			exit(1);	// 💥TEST
		}
	}
}

// 🖨️PRINT💥DEBUGING
void	print_node(t_ast *ast)
{
	t_ast *left;
	t_ast *right;
	t_ast *redir;

	if (ast->tag == AST_EXEC)
	{
		printf("%sprint_node.%s| [%sEXEC NODE%s]\n", B, RST, G, RST);
		printf("%sprint_node.%s| EXEC ARGS:", B, RST);
		for (int i = 0; i < ast->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, ast->data.ast_exec.argv[i], RST);
		printf("\n");
	}
	else if (ast->tag == AST_PIPE)
	{
		left = ast->data.ast_pipe.left;
		right = ast->data.ast_pipe.right;
		printf("%sprint_node.%s| [%sPIPE NODE%s]\n", B, RST, G, RST);
		if (left->tag == AST_EXEC)
		{
			printf("%sprint_node.%s| L. BRANCH:", B, RST);
			for (int i = 0; i < left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("%sprint_node.%s| L. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
		else if (left->tag == AST_REDIR)
			printf("%sprint_node.%s| L. BRANCH: [%sAST_REDIR%s]\n", B, RST, P, RST);
		if (right->tag == AST_EXEC)
		{
			printf("%sprint_node.%s| R. BRANCH:", B, RST);
			for (int i = 0; i < right->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, right->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (right->tag == AST_PIPE)
			printf("%sprint_node.%s| R. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
		else if (right->tag == AST_REDIR)
			printf("%sprint_node.%s| R. BRANCH: [%sAST_REDIR%s]\n", B, RST, P, RST);
		else
			printf("[%sEMPTY BRANCH%s]\n", B, RST);
	}
	else if (ast->tag == AST_REDIR)
	{
		left = ast->data.ast_redir.left;
		redir = ast;
		printf("%sprint_node.%s| [%sREDIR NODE%s]\n", B, RST, G, RST);
		if (left->tag == AST_EXEC)
		{
			printf("%sprint_node.%s| L. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
			printf("%sprint_node.%s| EXEC ARGS:", B, RST);
			for (int i = 0; i < ast->data.ast_redir.left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, ast->data.ast_redir.left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("%sprint_node.%s| L. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
		else if (left->tag == AST_REDIR)
			printf("%sprint_node.%s| L. BRANCH: [%sAST_REDIR%s]\n", B, RST, P, RST);
		if (redir->data.ast_redir.filename)
			printf("%sprint_node.%s| R. BRANCH: filename [%s%s%s] >> mode [%s%d%s]\n", B, RST, P, redir->data.ast_redir.filename, RST, P, redir->data.ast_redir.mode, RST);
	}
}
