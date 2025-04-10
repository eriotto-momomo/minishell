/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:17:14 by Timmi             #+#    #+#             */
/*   Updated: 2025/04/10 14:33:59 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*dupnewline(char *str)
{
	int		i;
	char	*newline;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	newline = malloc(i + 2);
	if (!newline)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		newline[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		newline[i++] = '\n';
	newline[i] = '\0';
	return (newline);
}

char	*conc(char *stach, char *buffer)
{
	int		i;
	int		j;
	char	*ptr;
	int		stach_len;
	int		buffer_len;

	i = -1;
	j = 0;
	stach_len = ft_strlen(stach);
	buffer_len = ft_strlen(buffer);
	if (!stach || !buffer)
		return (NULL);
	ptr = malloc((stach_len + buffer_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (stach)
		while (stach[++i] != '\0')
			ptr[i] = stach[i];
	while (buffer[j] != '\0')
		ptr[i++] = buffer[j++];
	ptr[stach_len + buffer_len] = '\0';
	free(stach);
	return (ptr);
}
