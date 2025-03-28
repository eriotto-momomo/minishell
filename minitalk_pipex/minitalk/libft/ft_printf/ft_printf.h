/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:34:54 by emonacho          #+#    #+#             */
/*   Updated: 2025/01/12 16:11:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		cnt_digits(unsigned int nbr);
int		ft_printf(const char *format, ...);
char	*ft_itoa_unsigned(unsigned int n);
void	printf_itoa_unsigned(unsigned int n, size_t *cnt);
void	printf_itoa(int n, size_t *cnt);
void	printf_putchar(char c, size_t *cnt);
void	printf_putstr(char *s, size_t *cnt);
void	puthex_dec(unsigned int to_convert, char spec, size_t *cnt);
int		printf_put_ptr(void *ptr, char spec, size_t *cnt);

#endif
