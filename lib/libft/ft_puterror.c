/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:32:53 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/09 00:03:26 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puterror(char *error_location, char *error_msg)
{
	ft_putstr_fd(Y, 2);
	ft_putstr_fd(error_location, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(R, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(RST, 2);
	ft_putstr_fd("\n", 2);
}
