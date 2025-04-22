/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/20 22:07:42 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast	*ast_new_node(t_ast cmd)
{
	t_ast	*ptr;

	//ptr = malloc(sizeof(t_ast));
	w_malloc((void**)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = cmd;
	return (ptr);
}
