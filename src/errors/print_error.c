/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 09:42:00 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(uint8_t *numerr, int err)
{
	char	*p_error;

	p_error = strerror(err);
	ft_puterror(p_error);
	*numerr = (uint8_t)err;
	return (err);
}

int	print_custom_error(uint8_t *numerr, int err, char *error_m)
{
	*numerr = (uint8_t)err;
	ft_putstr_fd(error_m, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (err);
}
