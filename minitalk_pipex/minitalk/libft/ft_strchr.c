/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:48:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/01/14 20:23:39 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if ((unsigned char)s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)s[i] == cc)
		return ((char *)&s[i]);
	return (0);
}
