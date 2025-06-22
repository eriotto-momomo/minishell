/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:09:34 by timmi             #+#    #+#             */
/*   Updated: 2025/06/22 14:14:07 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(const char *s1, const char *s2, const char *s3)
{
	char	*res;
	size_t	i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = '\0';
	return (res);
}
