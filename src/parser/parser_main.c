/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/20 09:23:26 by emonacho         ###   ########.fr       */
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
	print_list(s->head);
	if (syntax_analysis(temp))
	{
		free_list(&(s->head));
		return (1);
	}
	s->root_node = build_ast(&temp);
	printf("%s%s%s\n", Y, "============ ROOT NODE ============",RST); // 🖨️PRINT💥DEBUGING
	print_node(s->root_node); // 🖨️PRINT💥DEBUGING
	s->current_node = s->root_node;
	free_list(&(s->head));
	return (0);
}

