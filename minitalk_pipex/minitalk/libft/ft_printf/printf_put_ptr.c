/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:28:52 by emonacho          #+#    #+#             */
/*   Updated: 2025/01/12 16:11:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	puthex_ptr(unsigned long long to_convert, char spec, size_t *cnt)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (to_convert > 15)
		puthex_ptr(to_convert / 16, spec, cnt);
	printf_putchar(hex[to_convert % 16], cnt);
}

int	printf_put_ptr(void *ptr, char spec, size_t *cnt)
{
	unsigned long long	castptr;

	castptr = (unsigned long long)ptr;
	if (ptr == 0)
		printf_putstr("0x0", cnt);
	else
	{
		printf_putstr("0x", cnt);
		puthex_ptr(castptr, spec, cnt);
	}
	return (0);
}
