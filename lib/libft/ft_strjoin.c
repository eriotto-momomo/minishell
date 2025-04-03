/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:52:28 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/03 12:38:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*ptr;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((len * sizeof(char)) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t		s1_len;
// 	size_t		s2_len;
// 	char		*new_s;

// 	s1_len = ft_strlen (s1);
// 	s2_len = ft_strlen (s2);
// 	new_s = malloc(sizeof(char) * (s1_len + s2_len) + 1);
// 	if (!new_s)
// 		return (0);
// 	ft_memcpy(new_s, s1, s1_len);
// 	ft_memcpy((new_s + s1_len), s2, s2_len);
// 	new_s[s1_len + s2_len] = '\0';
// 	free(s1);
// 	return (new_s);
// }
