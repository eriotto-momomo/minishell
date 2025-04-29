/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:08:35 by c4v3d             #+#    #+#             */
/*   Updated: 2025/04/29 11:23:23 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(char **args, int fd_out)
{
	char 	*temp;
	int 	ret;
	int 	i;
	int 	append;

	i = 1;
	ret = 0;
	append = 1;
	if (ft_memcmp(args[i], "-n", 2))
		append = 0;
	while (args[i])
	{
		
		temp = ft_strjoin(args[i], " ");
		ret = write(fd_out, temp, ft_strlen(temp));
		if (ret == -1)
			return (ret);
		free(temp);
		i++;
	}
	write(fd_out, "\n", 1);
	return (ret);
}
