/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 20:16:41 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	add_heredoc(t_ast **node, t_token **tok)
{
	(*node)->data.s_exec.heredoc_count = count_tokens(&(*tok), HERE_DOC);
	if ((*node)->data.s_exec.heredoc_count == 0)
		return (0);
	(*node)->data.s_exec.heredoc_list
		= copy_heredocs(*tok, (*node)->data.s_exec.heredoc_count);
	if (!(*node)->data.s_exec.heredoc_list)
		return (1);
	return (0);
}

int	add_redir(t_ast **node, t_token **tok)
{
	t_token	*tmp;

	(*node)->data.s_exec.fd_in = 0;
	(*node)->data.s_exec.fd_out = 1;
	tmp = *tok;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUT_REDIR || tmp->type == APP_OUT_REDIR)
			(*node)->data.s_exec.fd_out
				= redir_out(tmp->type, tmp->next->data,
					(*node)->data.s_exec.fd_out);
		else if (tmp->type == IN_REDIR)
			(*node)->data.s_exec.fd_in
				= redir_in(tmp->next->data, (*node)->data.s_exec.fd_in);
		if ((*node)->data.s_exec.fd_out < 0 || (*node)->data.s_exec.fd_in < 0)
		{
			errno = 2;
			return (1);
		}
		if (!get_next_token(&tmp))
			break ;
	}
	return (0);
}

t_ast	*add_exec_node(t_token **tok)
{
	t_ast	*node;

	node = new_ast_node((t_ast){0});
	if (!node)
		return (NULL);
	if (add_command(&node, tok) != 0)
		return (NULL);
	if (add_heredoc(&node, tok) != 0)
	{
		ft_free_char_array(node->data.s_exec.av, node->data.s_exec.ac);
		return (NULL);
	}
	if (add_redir(&node, tok) != 0)
	{
		ft_free_char_array(node->data.s_exec.av, node->data.s_exec.ac);
		ft_free_char_array(node->data.s_exec.heredoc_list,
			node->data.s_exec.heredoc_count);
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
