/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/25 15:24:33 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*build_ast(t_shell *s, t_token **tok)
{
	t_ast	*ast;

	ast = parse_line(s, tok);
	if (!ast)
		return (NULL);
	return (ast);
}

int	parser(t_shell *s)
{
	t_token	*tmp;

	tmp = s->head;
	if (syntax_analysis(s, tmp) != 0)
		return (1);
	s->root_node = build_ast(s, &tmp);
	if (!s->root_node)
	{
		if (errno == 0)
			errno = ENOMEM;
		return (print_error(&s->numerr, NULL, errno));
	}
	s->current_node = s->root_node;
	if (s->heredoc_count > 0)
		fill_heredocs(s);
	free_token_list(&(s->head));
	return (0);
}
