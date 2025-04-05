/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:25:21 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 20:49:07 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 'if (nmemb > SIZE_MAX / size)' check for integer overflow
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*new_str;
	size_t			total_size;

	if (nmemb > SIZE_MAX / size || nmemb == 0 || size == 0)
	{
		if (nmemb == 0 || size == 0)
			errno = EINVAL;
		else
			errno = EOVERFLOW;
		return (NULL);
	}
	total_size = nmemb * size;
	new_str = malloc(total_size);
	if (new_str == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (total_size > 0)
	{
		new_str[total_size] = 0;
		total_size--;
	}
	new_str[total_size] = 0;
	return (new_str);
}
