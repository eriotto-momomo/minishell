/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 17:05:26 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*pathfinder(char *cmd, char **path)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free (full_path);
		i++;
	}
	printf("No path found...\n");
	return (NULL);
}

void	cmd_execution(char **cmd, char **path)
{
	char	*cmd_path;

	cmd_path = pathfinder(cmd[0], path);
	if (!cmd_path)
		printf("No path Found...\n");
	if (execve(cmd_path, cmd, path) == -1)
	{
		printf("Failed execve\n");
		
	}
}
