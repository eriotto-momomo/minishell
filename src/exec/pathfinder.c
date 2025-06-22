/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:00:57 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/22 17:34:24 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*make_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	if (!full_path)
		return (NULL);
	free(tmp);
	return (full_path);
}

char	*pathfinder(t_env *env, char *cmd)
{
	int		i;
	char	**path;
	char	*full_path;

	i = -1;
	path = ft_split(ft_getenv(env, "PATH"), ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		full_path = make_path(path[i], cmd);
		if (!full_path)
			return (ft_free_char_array(path, ft_count_tab(path, 0)));
		if (access(full_path, F_OK) == 0)
		{
			ft_free_char_array(path, ft_count_tab(path, 0));
			return (full_path);
		}
		free (full_path);
	}
	ft_free_char_array(path, ft_count_tab(path, 0));
	return (NULL);
}
