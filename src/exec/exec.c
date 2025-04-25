/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 22:26:41 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*pathfinder(char *cmd)
{
	int		i;
	char	**path;
	char	*full_path;
	char	*temp;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array(path, ft_count_tab(path, 0), 'c');
			return (full_path);
		}
		free (full_path);
		i++;
	}
	ft_free_array(path, ft_count_tab(path, 0), 'c');
	return (NULL);
}

void	cmd_execution(char **cmd, char **envp)
{
	char	*cmd_path;
	
	
	cmd_path = pathfinder(cmd[0]);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(127);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		free(cmd_path);
		perror("Command not executable");
		exit(126);
	}
}

void	simple_cmd(t_ast *node, char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == 0)
		cmd_execution(node->data.ast_exec.argv, envp);
	waitpid(pid1, NULL, 0);
}
