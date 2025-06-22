/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 18:07:20 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*build_ast(t_token **tok)
{
	t_ast	*ast;

	ast = parse_line(tok);
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
	s->heredoc_list = NULL;
	s->heredoc_count = 1;
	s->root_node = build_ast(&tmp);
	if (!s->root_node)
		return (print_error(&s->numerr, ENOMEM, "build_ast"));
	s->current_node = s->root_node;
	free_token_list(&(s->head));
	return (0);
}
