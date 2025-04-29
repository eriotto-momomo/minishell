/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:08:35 by c4v3d             #+#    #+#             */
/*   Updated: 2025/04/29 15:32:49 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	len_calc(char **tab)
{
	size_t	total_len;
	int		i;

	i = 1;
	total_len = 0;
	while (tab[i])
	{
		total_len += ft_strlen(tab[i]);
		if (tab[i + 1])
			total_len += 1;
		i++;
	}
	return (total_len);
}

static char	*tabtos(char **tab)
{
	char 	*ptr;
	int		i;
	size_t	total_len;
	char	*final_str;
	int		len;
	
	i = 1;
	len = 0;
	total_len = len_calc(tab);
	final_str = malloc(total_len + 1);
	if (!final_str)
		return (NULL);
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		ft_memcpy(ptr, tab[i], len);
		ptr += len;
		if (tab[i + 1])
		{
			*ptr = ' ';
			ptr++;
		}
		i++;
	}
	*ptr = '\0';
	printf("str :%s\n", final_str);
	return (final_str);
}

int	ft_echo(char **args, int fd_out)
{
	char	*str;

	if (args[1])
		str = tabtos(args);
	write(fd_out, str, ft_strlen(str));
	return (1);
}