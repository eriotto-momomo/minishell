/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:00:57 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/25 12:30:22 by timmi            ###   ########.fr       */
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

static int	is_path(const char *cmd)
{
	if (!cmd)
		return (0);
	return (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/'
				|| (cmd[1] == '.' && cmd[2] == '/'))));
}

char	*path_making(t_env *env, char *cmd)
{
	char	*cmd_path;

	if (is_path(cmd))
	{
		cmd_path = ft_strdup(cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == -1)
		{
			w_free((void **)&cmd_path);
			return (NULL);
		}
	}
	else
	{
		cmd_path = pathfinder(env, cmd);
		if (!cmd_path)
			return (NULL);
	}
	return (cmd_path);
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
