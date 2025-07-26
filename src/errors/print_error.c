/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/07/18 15:12:40 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(uint8_t *numerr, char *str, int err)
{
	char	*p_error;

	errno = err;
	p_error = strerror(err);
	*numerr = (uint8_t)err;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str != NULL)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
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
