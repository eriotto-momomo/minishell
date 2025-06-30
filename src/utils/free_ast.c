/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:37:22 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/30 09:09:06 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_pipe_node(t_ast *node)
{
	if (node->data.s_pipe.left)
	{
		if (node->data.s_pipe.left->tag == EXEC_NODE)
			free_exec_node(node->data.s_pipe.left);
		else if (node->data.s_pipe.left->tag == PIPE_NODE)
			free_pipe_node(node->data.s_pipe.left);
	}
	if (node->data.s_pipe.right)
	{
		if (node->data.s_pipe.right->tag == EXEC_NODE)
			free_exec_node(node->data.s_pipe.right);
		else if (node->data.s_pipe.right->tag == PIPE_NODE)
			free_pipe_node(node->data.s_pipe.right);
	}
	w_free((void **)&node);
}

void	free_exec_node(t_ast *node)
{
	ft_free_char_array(node->data.s_exec.av, node->data.s_exec.ac);
	node->data.s_exec.ac = 0;
	if (node->data.s_exec.eof_count > 0)
	{
		ft_free_char_array(node->data.s_exec.eof_list,
			node->data.s_exec.eof_count);
		node->data.s_exec.eof_count = 0;
	}
	node->data.s_exec.fd_in = 0;
	node->data.s_exec.fd_out = 1;
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
}
