/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/04/30 13:37:46 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*save_cwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("Cannot get current directory: ");
		if (errno == ERANGE)
			perror("Buffer size too small: ");
		return (NULL);
	}
	return(ft_strdup(buffer));
}

int	ft_cd(t_shell *s)
{
	s->old_path = save_cwd();
	if (!s->old_path)
		return (1);
	
	return(0);
}