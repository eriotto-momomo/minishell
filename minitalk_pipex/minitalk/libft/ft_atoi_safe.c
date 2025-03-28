/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:39:16 by emonacho          #+#    #+#             */
/*   Updated: 2025/02/11 18:06:04 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_safe(const char *str, int *error)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (((str[i]) >= 9 && (str[i]) <= 13) || (str[i]) == 32)
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + (str[i++] - '0');
		if ((num * sign) < -2147483648 || (num * sign) > 2147483647)
			*error = -1;
	}
	num *= sign;
	return (num);
}
