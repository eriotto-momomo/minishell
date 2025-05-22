/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/22 17:11:31 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_next_token(t_list **tok)
{
	if ((*tok) && (*tok)->next)
		*tok = (*tok)->next;
}

char	*fill_exec_node(t_list *tok)
{
	char	*arg;

	if (!tok)
		return (NULL);
	arg = ft_strdup(tok->data);
	if (!arg)
	{
		errno = ENOMEM;
		ft_puterror("fill_exec_node", strerror(errno));
		return (NULL);
	}
	return (arg);
}

// 🖨️PRINT💥DEBUGING
void	print_node(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*redir;

	if (ast->tag == AST_EXEC)
	{
		printf("%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		printf("%sprint_node%s| argc: %d\n", B, RST, ast->data.ast_exec.argc);
		printf("%sprint_node%s| args:", B, RST);
		//for (int i = 0; i < ast->data.ast_exec.argc; i++)
		//		printf(" [%s%s%s]", C, ast->data.ast_exec.argv[i], RST);
		int i = 0;
		while (ast->data.ast_exec.argv[i])
		{
			printf(" [%s%s%s]", C, ast->data.ast_exec.argv[i], RST);
			i++;
		}
		printf("\n");
	}
	else if (ast->tag == AST_PIPE)
	{
		left = ast->data.ast_pipe.left;
		right = ast->data.ast_pipe.right;
		printf("%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		if (left->tag == AST_EXEC)
		{
			printf("%sprint_node%s| L. BRANCH:", B, RST);
			printf(" [%sAST_EXEC%s]", P, RST);
			for (int i = 0; i < left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("%sprint_node%s| L. BRANCH: [%sAST_PIPE%s]\n", B, RST, P, RST);
		else if (left->tag == AST_REDIR)
			printf("%sprint_node%s| L. BRANCH: [%sAST_REDIR%s]\n", B, RST, P, RST);
		if (right->tag == AST_EXEC)
		{
			printf("%sprint_node%s| R. BRANCH:", B, RST);
			printf(" [%sAST_EXEC%s]", P, RST);
			for (int i = 0; i < right->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, right->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (right->tag == AST_PIPE)
			printf("%sprint_node%s| R. BRANCH: [%sAST_PIPE%s]\n", B, RST, P, RST);
		else if (right->tag == AST_REDIR)
			printf("%sprint_node%s| R. BRANCH: [%sAST_REDIR%s]\n", B, RST, P, RST);
		else
			printf("[%sEMPTY BRANCH%s]\n", B, RST);
	}
	else if (ast->tag == AST_REDIR)
	{
		left = ast->data.ast_redir.left;
		redir = ast;
		printf("%sprint_node%s| %sREDIR NODE%s\n", B, RST, G, RST);
		if (left->tag == AST_EXEC)
		{
			printf("%sprint_node%s| L. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
			printf("%sprint_node%s| args:", B, RST);
			for (int i = 0; i < ast->data.ast_redir.left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, ast->data.ast_redir.left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("%sprint_node%s| L. BRANCH: [%sAST_EXEC%s]\n", B, RST, P, RST);
		else if (left->tag == AST_REDIR)
			printf("%sprint_node%s| L. BRANCH: [%sAST_REDIR%s] filename[%s%s%s]\n", B, RST, P, RST, P, redir->data.ast_redir.left->data.ast_redir.filename, RST);
		if (redir->data.ast_redir.filename)
			printf("%sprint_node%s| R. BRANCH: filename [%s%s%s] >> mode [%s%d%s]\n", B, RST, P, redir->data.ast_redir.filename, RST, P, redir->data.ast_redir.mode, RST);
	}
}
