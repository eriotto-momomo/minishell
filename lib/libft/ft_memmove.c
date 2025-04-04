/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:35 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 16:08:25 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = dst;
	ptr_src = src;
	if (ptr_dst == 0 && ptr_src == 0)
		return (NULL);
	if (ptr_dst <= ptr_src)
	{
		while (len-- > 0)
			*ptr_dst++ = *ptr_src++;
	}
	else if (dst > src)
	{
		ptr_dst += len - 1;
		ptr_src += len - 1;
		while (len-- > 0)
			*ptr_dst-- = *ptr_src--;
	}
	return (dst);
}
