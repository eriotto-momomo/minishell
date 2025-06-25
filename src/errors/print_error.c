/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 10:38:23 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(uint8_t *numerr, int err)
{
	char	*p_error;

	errno = err;
	p_error = strerror(err);
	*numerr = (uint8_t)err;
	ft_puterror(p_error);
	return (err);
}

int	print_custom_error(uint8_t *numerr, int err, char *error_m)
{
	errno = err;
	*numerr = (uint8_t)err;
	ft_putstr_fd(error_m, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (err);
}
