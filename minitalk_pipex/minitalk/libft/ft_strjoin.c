/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:52:28 by emonacho          #+#    #+#             */
/*   Updated: 2025/01/14 20:24:24 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	char		*new_s;

	s1_len = ft_strlen (s1);
	s2_len = ft_strlen (s2);
	new_s = malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!new_s)
		return (0);
	ft_memcpy(new_s, s1, s1_len);
	ft_memcpy((new_s + s1_len), s2, s2_len);
	new_s[s1_len + s2_len] = '\0';
	free(s1);
	return (new_s);
}
