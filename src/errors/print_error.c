/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 13:50:33 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	syntax_error(int err)
{
	if (err == UNEXPECTED_TOK)
		ft_putstr_fd("Unexpected token found!\n", STDERR_FILENO);
	else if (err == UNMATCHED_QUOTE)
		ft_putstr_fd("Unmactched quote found!\n", STDERR_FILENO);
}

void	print_error(int err)
{
	if (err < 5)
		syntax_error(err);
	// else if (err < 10 && err > 5)
	// 	lexer_error(err);
}