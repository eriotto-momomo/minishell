/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:20:28 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/07 15:50:53 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *s, int fd_out)
{
	int		i;
	char	*output;
	char	*temp;

	i = 0;
	output = ft_calloc(1, 1);
	while (s->env[i])
	{
		temp = ft_strjoin(output, s->env[i]);
		free(output);
		output = ft_strjoin(temp, "\n");
		free(temp);
		i++;
	}
	if (output)
	{
		ft_putstr_fd(output, fd_out);
		free(output);
	}
}