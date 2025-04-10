/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:12:10 by Timmi             #+#    #+#             */
/*   Updated: 2025/04/10 14:34:50 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !str[i + 1])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc((ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

static char	*fill_stach(int fd, char *stach)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stach, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stach);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stach = conc(stach, buffer);
		if (!stach)
			return (NULL);
	}
	free(buffer);
	return (stach);
}

char	*get_next_line(int fd)
{
	char			*newline;
	static char		*stach;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!stach)
	{
		stach = malloc(1 * sizeof(char));
		if (!stach)
			return (NULL);
		stach[0] = '\0';
	}
	stach = fill_stach(fd, stach);
	if (!stach)
		return (NULL);
	newline = dupnewline(stach);
	stach = ft_trim(stach);
	return (newline);
}
// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
//     int i = 0;
//     const char	*path;
//     int			fd;
//     path = "words.txt";
//     fd = open(path, O_RDONLY);
//     while (i <= 2)
//     {
// 	    printf("%s", get_next_line(fd));
//         i++;
//     }
//     return (0);
// }