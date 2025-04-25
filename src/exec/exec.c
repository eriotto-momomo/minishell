/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 14:52:05 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*pathfinder(char *path, char *cmd)
{
	int		i;
	char	**m_path;
	char	*full_path;
	char	*temp;

	i = 0;
	m_path = ft_split(path, ':');
	while (m_path[i])
	{
		temp = ft_strjoin(m_path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array(m_path, ft_count_tab(m_path, 0), 'c');
			printf("Found a path!\n");
			return (full_path);
		}
		free (full_path);
		i++;
	}
	ft_free_array(m_path, ft_count_tab(m_path, 0), 'c');
	printf("No path found...\n");
	return (NULL);
}

void	execution(char **cmd)
{
	char	*m_path;
	char	*cmd_path;

	m_path = getenv("PATH");
	if (!m_path)
		printf("No env\n");
	cmd_path = pathfinder(m_path, cmd[0]);
	if (!cmd_path)
	{
		free(m_path);
		return (0); // replace with exit
	}
	if (execve(cmd_path, cmd, m_path) == -1)
	{
		
	}
}