/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/21 18:55:15 by emonacho         ###   ########.fr       */
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
	//print_list(s->head);												// 🖨️PRINT💥DEBUGING
	if (syntax_analysis(temp) != 0)
	{
		//terminate_shell(s, errno);
		return (1);
	}
	s->root_node = build_ast(&temp);
	if (!s->root_node)
	{
		terminate_shell(s, errno);
		return (1);
	}
	//printf("%s%s%s\n", Y, "============ ROOT NODE ============",RST); // 🖨️PRINT💥DEBUGING
	//print_node(s->root_node); 										// 🖨️PRINT💥DEBUGING
	//printf("%s%s%s\n", Y, "============ ********* ============",RST); // 🖨️PRINT💥DEBUGING
	s->current_node = s->root_node;
	free_list(&(s->head));
	return (0);
}

