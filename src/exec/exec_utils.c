/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/16 21:38:46 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pipe(int	fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

char	*pathfinder(t_env *env, char *cmd)
{
	int		i;
	char	**path;
	char	*full_path;
	char	*temp;

	i = 0;
	path = ft_split(ft_getenv(env, "PATH"), ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_char_array(path, ft_count_tab(path, 0));
			return (full_path);
		}
		free (full_path);
		i++;
	}
	ft_free_char_array(path, ft_count_tab(path, 0));
	return (NULL);
}

int	cmd_execution(t_env *env, char **argv)
{
	char	*cmd_path;

	cmd_path = pathfinder(env, argv[0]);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(127);
	}
	if (execve(cmd_path, argv, NULL) == -1)
	{
		w_free((void **)&cmd_path);
		perror("Command not executable");
		exit(126);
	}
	return (0);
}
