/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:24:21 by timmi             #+#    #+#             */
/*   Updated: 2025/06/22 17:13:31 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(uint8_t *numerr, int err, char *f)
{
	char	*p_error;

	p_error = strerror(err);
	ft_puterror(f, p_error);
	*numerr = (uint8_t)err;
	return (err);
}

int	print_custom_error(uint8_t *numerr, int err, char *error_m)
{
	*numerr = (uint8_t)err;
	ft_putstr_fd(error_m, STDERR_FILENO);
	return (err);
}
