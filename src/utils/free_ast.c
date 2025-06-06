/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:37:22 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/06 17:59:19 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_pipe_node(t_ast *node)
{
	if (node->data.pipe.left)
	{
		if (node->data.pipe.left->tag == EXEC_NODE)
			free_exec_node(node->data.pipe.left);
		else if (node->data.pipe.left->tag == PIPE_NODE)
			free_pipe_node(node->data.pipe.left);
	}
	if (node->data.pipe.right)
	{
		if (node->data.pipe.right->tag == EXEC_NODE)
			free_exec_node(node->data.pipe.right);
		else if (node->data.pipe.right->tag == PIPE_NODE)
			free_pipe_node(node->data.pipe.right);
	}
	w_free((void **)&node);
	//printf("%s🔶FREE PIPE_NODE.|%s %sFREED!%s\n", Y, RST, G, RST); // PRINT DEBUGGING 📠
}

void	free_exec_node(t_ast *node)
{
	int	i;


	//printf("%s🔵FREE EXEC_NODE.|%s %sFREED!%s\n", B, RST, G, RST); // PRINT DEBUGGING 📠

	//🚨REMPLACER PAR FT_FREE_CHAR_ARRAY🚨
	i = 0;
	if (node->data.exec.argc > 0)
	{
		while (node->data.exec.argv[i] && i < node->data.exec.argc)
		{
			//printf("%sargv[%d]%s[%s] ", B, i, RST, node->data.exec.argv[i]); // PRINT DEBUGGING 📠
			w_free((void **)&node->data.exec.argv[i]);
			i++;
		}
		w_free((void **)&node->data.exec.argv);
		node->data.exec.argc = 0;
		//printf("\n"); // PRINT DEBUGGING 📠
	}

	//🚨REMPLACER PAR FT_FREE_CHAR_ARRAY🚨
	i = 0;
	if (node->data.exec.heredoc_count > 0)
	{
		while (node->data.exec.heredoc_list[i] && i < node->data.exec.heredoc_count)
		{
			//printf("%sheredoc_list[%d]%s[%s] ", B, i, RST, node->data.exec.heredoc_list[i]); // PRINT DEBUGGING 📠
			w_free((void **)&node->data.exec.heredoc_list[i]);
			i++;
		}
		w_free((void **)&node->data.exec.heredoc_list);
		node->data.exec.heredoc_count = 0;
		//printf("\n"); // PRINT DEBUGGING 📠
	}
	node->data.exec.fd_in = 0;
	node->data.exec.fd_out = 0;
	w_free((void **)&node);
}

void	free_ast(t_ast **node)
{
	if (!node)
		return ;
	if (node && (*node)->tag == PIPE_NODE)
		free_pipe_node(*node);
	else if (node && (*node)->tag == EXEC_NODE)
		free_exec_node(*node);
	*node = NULL;
	//printf("%s🔥AST FREED🔥%s\n", G, RST); // PRINT DEBUGGING 📠
}
