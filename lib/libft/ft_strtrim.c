/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:07:19 by emonacho          #+#    #+#             */
/*   Updated: 2025/01/14 20:23:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = ft_strlen(s1);
	i = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (s1[start] && to_trim(set, s1[start]))
		start++;
	while (end > start && to_trim(set, s1[end - 1]))
		end--;
	res = (char *)malloc((end - start + 1) * sizeof(char));
	if (res == 0)
		return (NULL);
	while (start < end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
