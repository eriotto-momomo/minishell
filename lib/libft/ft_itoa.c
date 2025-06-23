/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:28:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 18:52:24 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isnegative(int nbr)
{
	if (nbr < 0)
		return (1);
	else
		return (0);
}

static int	cntdigits(unsigned int nbr)
{
	size_t	digits;

	if (nbr == 0)
		return (1);
	digits = 0;
	while (nbr >= 1)
	{
		nbr /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	neg;
	unsigned int	nbr;
	unsigned int	digits;

	neg = isnegative(n);
	if (neg)
		nbr = -n;
	else
		nbr = n;
	digits = cntdigits(nbr);
	str = (char *)malloc(digits + neg + 1);
	if (str == 0)
		return (NULL);
	if (neg == 1)
		str[0] = '-';
	str[digits + neg] = '\0';
	while (digits > 0)
	{
		str[(digits - 1) + neg] = (nbr % 10) + '0';
		nbr /= 10;
		digits--;
	}
	return (str);
}
