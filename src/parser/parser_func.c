/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/13 11:18:40 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_pipe(t_list **tok)
{
	t_ast	*right;
	t_ast	*left;

	if (!*tok || (*tok)->data == NULL)
		return (NULL);
	left = parse_exec(tok);
	if (!left)
		return (NULL);
	while (*tok && (*tok)->type == PIPE)
	{
		if (!get_next_token(tok))
			return (left);
		right = parse_exec(tok);
		if (!right)
			return (NULL);
		left = add_pipe_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*parse_line(t_list **tok)
{
	t_ast	*node;

	node = parse_pipe(tok);
	if (!node)
		return (NULL);
	return (node);
}

t_ast	*parse_exec(t_list **tok)
{
	t_ast	*exec_node;

	if ((*tok) && (*tok)->type != PIPE)
	{
		exec_node = add_exec_node(tok);
		if (!exec_node)
			return (NULL);
		get_next_pipe(tok);
	}
	return (exec_node);
}

void	get_next_pipe(t_list **tok)
{
	while ((*tok) && (*tok)->type != PIPE)
	{
		if (!get_next_token(tok))
			break;
	}
}

int	get_next_token(t_list **tok)
{
	if (!(*tok) || !(*tok)->next)
		return (0);
	*tok = (*tok)->next;
	return (1);
}
