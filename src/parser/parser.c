/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 17:24:34 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast *parse_tokens(t_list **head)
{
	t_ast *ast;

	ast = parse_line(head);
	return (ast);
}

t_ast *parser(t_list *head)
{
	if (!syntax_analysis(head))
		return (NULL);
	return (parse_tokens(&head));
}