/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/16 19:40:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*build_ast(t_list **tok)
{
	t_ast	*ast;

	ast = parse_line(tok);
	return (ast);
}

int	parser(t_shell *s)
{
	t_list *temp;

	temp = s->head;
	if (syntax_analysis(temp))
	{
		free_list(&(s->head));
		return (1);
	}
	s->root_node = build_ast(&temp);
	s->current_node = s->root_node;
	free_list(&(s->head));
	return (0);
}

