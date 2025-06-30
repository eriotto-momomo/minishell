/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/30 09:11:15 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_pipe(t_shell *s, t_token **tok)
{
	t_ast	*right;
	t_ast	*left;

	if (!*tok || (*tok)->data == NULL)
		return (NULL);
	left = parse_exec(s, tok);
	if (!left)
		return (NULL);
	while (*tok && (*tok)->type == PIPE)
	{
		if (!get_next_token(tok))
			return (left);
		right = parse_exec(s, tok);
		if (!right)
			return (NULL);
		left = add_pipe_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*parse_line(t_shell *s, t_token **tok)
{
	t_ast	*node;

	// COPIER LA LISTE DE TOUS LA HEREDOC QU'ON UTILISE COMME INPUT
	if (s->tmp_files_list == NULL)
	{
		s->heredoc_count = count_all_heredocs(*tok);
		if (s->heredoc_count > 0)
		{
			s->tmp_files_list = malloc(sizeof(char*) * s->heredoc_count);
			if (!s->tmp_files_list)
				return (NULL);
		}
		fprintf(stderr, "%sget_heredoc | INITIALIZING s->tmp_files_list%s\n", Y, RST);
	}
	node = parse_pipe(s, tok);
	if (!node)
		return (NULL);
	return (node);
}

t_ast	*parse_exec(t_shell *s, t_token **tok)
{
	t_ast	*exec_node;

	if ((*tok) && (*tok)->type != PIPE)
	{
		exec_node = add_exec_node(s, tok);
		if (!exec_node)
			return (NULL);
		errno = 0;
		s->numerr = 0;
		get_next_pipe(tok);
	}
	return (exec_node);
}

void	get_next_pipe(t_token **tok)
{
	while ((*tok) && (*tok)->type != PIPE)
	{
		if (!get_next_token(tok))
			break ;
	}
}

int	get_next_token(t_token **tok)
{
	if (!(*tok) || !(*tok)->next)
		return (0);
	*tok = (*tok)->next;
	return (1);
}
