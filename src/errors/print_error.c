/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 19:05:58 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	syntax_error(int err)
// {
// 	if (err == UNEXPECTED_TOK)
// 		ft_putstr_fd("Unexpected token found!\n", STDERR_FILENO);
// 	else if (err == UNMATCHED_QUOTE)
// 		ft_putstr_fd("Unmactched quote found!\n", STDERR_FILENO);
// }

// void	print_error(int err)
// {
// 	if (err < 5)
// 		syntax_error(err);
// 	// else if (err < 10 && err > 5)
// 	// 	lexer_error(err);
// }

int	print_error(int err, char *f)
{
	char	*p_error;
	
	p_error = strerror(err);
	ft_puterror(f, p_error);
	g_status = (uint8_t)err;
	return (err);
}