/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:37:22 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/27 18:33:12 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_pipe_node(t_ast *node)
{
	if (node->data.ast_pipe.left)
	{
		if (node->data.ast_pipe.left->tag == AST_EXEC)
			free_exec_node(node->data.ast_pipe.left);
		else if (node->data.ast_pipe.left->tag == AST_PIPE)
			free_pipe_node(node->data.ast_pipe.left);
		else if (node->data.ast_pipe.left->tag == AST_REDIR)
			free_redir_node(node->data.ast_pipe.left);
	}
	if (node->data.ast_pipe.right)
	{
		if (node->data.ast_pipe.right->tag == AST_EXEC)
			free_exec_node(node->data.ast_pipe.right);
		else if (node->data.ast_pipe.right->tag == AST_PIPE)
			free_pipe_node(node->data.ast_pipe.right);
		else if (node->data.ast_pipe.right->tag == AST_REDIR)
			free_redir_node(node->data.ast_pipe.right);
	}
	w_free((void **)&node);
	printf("%s🔶FREE PIPE_NODE.|%s %sFREED!%s\n", Y, RST, G, RST); // PRINT DEBUGGING 📠
}

void	free_redir_node(t_ast *node)
{
	if (node->data.ast_redir.left)
	{
		if (node->data.ast_redir.left->tag == AST_EXEC)
			free_exec_node(node->data.ast_redir.left);
		else if (node->data.ast_redir.left->tag == AST_PIPE)
			free_pipe_node(node->data.ast_redir.left);
		else if (node->data.ast_redir.left->tag == AST_REDIR)
			free_redir_node(node->data.ast_redir.left);
	}
	node->data.ast_redir.mode = 0;
	w_free((void **)&node->data.ast_redir.filename);
	w_free((void **)&node);
	printf("%s🔴FREE REDIR_NODE|%s %sFREED!%s\n", R, RST, G, RST); // PRINT DEBUGGING 📠
}

void	free_exec_node(t_ast *node)
{
	int	i;

	if (node->data.ast_exec.argv && node->data.ast_exec.argv[0]
			&& node->data.ast_exec.argc > 0)
	{
		i = 0;
		printf("%s🔵FREE EXEC_NODE.|%s %sFREED!%s", B, RST, G, RST); // PRINT DEBUGGING 📠
		// 🚨TEST🚨 **argv is allocated with more slots than usually required (10)
		while (node->data.ast_exec.argv[i])
		{
			printf(" %sargv[%d]%s[%s]", B, i, RST, node->data.ast_exec.argv[i]); // PRINT DEBUGGING 📠
			if (ft_strncmp(node->data.ast_exec.argv[i], "./tmp/heredoc_tmp.txt",
					ft_strlen(node->data.ast_exec.argv[i])))
				unlink("./tmp/heredoc_tmp.txt");
			w_free((void **)&node->data.ast_exec.argv[i]);
			i++;
		}
		printf("\n"); // PRINT DEBUGGING 📠

		// BACKUP 💾
		//while (i < node->data.ast_exec.argc)
		//{
		//	//printf(" %sargv[%d]%s[%s]", B, i, RST, node->data.ast_exec.argv[i]); // PRINT DEBUGGING 📠
		//	w_free((void **)&node->data.ast_exec.argv[i]);
		//	i++;
		//}

		node->data.ast_exec.argc = 0;
		w_free((void **)&node->data.ast_exec.argv);
		w_free((void **)&node);
	}
}

void	free_ast(t_ast **node)
{
	if (!node)
		return ;
	if (node && (*node)->tag == AST_PIPE)
		free_pipe_node(*node);
	else if (node && (*node)->tag == AST_REDIR)
		free_redir_node(*node);
	else if (node && (*node)->tag == AST_EXEC)
		free_exec_node(*node);
	*node = NULL;
	printf("%s🔥AST FREED🔥%s\n", G, RST); // PRINT DEBUGGING 📠
}
