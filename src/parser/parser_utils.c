/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/19 19:12:43 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Adapté de: https://keleshev.com/abstract-syntax-tree-an-example-in-c/
t_ast	*ast_new_node(t_ast ast)
{
	t_ast	*ptr;

	//ptr = malloc(sizeof(t_ast));
	w_malloc((void**)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = ast;
	return (ptr);
}
