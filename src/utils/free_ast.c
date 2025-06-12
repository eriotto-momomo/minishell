/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:37:22 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/12 16:36:31 by emonacho         ###   ########.fr       */
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
	if (node->data.exec.argc > 0)
	{
		ft_free_char_array(node->data.exec.argv, node->data.exec.argc);
		node->data.exec.argc = 0;
	}
	if (node->data.exec.heredoc_count > 0)
	{
		ft_free_char_array(node->data.exec.heredoc_list, node->data.exec.heredoc_count);
		node->data.exec.heredoc_count = 0;
	}
	node->data.exec.fd_in = 0;
	node->data.exec.fd_out = 0;
	w_free((void **)&node);
	//printf("%s🔵FREE EXEC_NODE.|%s %sFREED!%s\n", B, RST, G, RST); // PRINT DEBUGGING 📠
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
