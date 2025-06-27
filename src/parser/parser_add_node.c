/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 12:29:12 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	add_redir(t_shell *s, t_ast **node, t_token **tok)
{
	get_heredoc(s, &node, tok);
	get_redir(s, &node, tok);
	//check_priority;
}

int	add_command(t_ast **node, t_token **tok)
{
	(*node)->tag = EXEC_NODE;
	(*node)->data.s_exec.ac = count_tokens(&(*tok), WORD);
	if ((*node)->data.s_exec.ac < 0)
		return (1);
	(*node)->data.s_exec.av = copy_args(*tok, (*node)->data.s_exec.ac);
	if (!(*node)->data.s_exec.av)
		return (1);
	(*node)->data.s_exec.fd_in = STDIN_FILENO;
	(*node)->data.s_exec.fd_out = STDOUT_FILENO;
	return (0);
}

t_ast	*add_exec_node(t_shell *s, t_token **tok)
{
	t_ast	*node;

	node = new_ast_node((t_ast){0});
	if (!node)
		return (NULL);
	if (add_command(&node, tok) != 0)
	{
		w_free((void **)&node);
		return (NULL);
	}
	if (add_redir(s, &node, tok) != 0)
	{
		w_free((void **)&node);
		return (NULL);
	}
	return (node);
}

t_ast	*add_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	node = new_ast_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = PIPE_NODE;
	node->data.s_pipe.left = left;
	node->data.s_pipe.right = right;
	return (node);
}
