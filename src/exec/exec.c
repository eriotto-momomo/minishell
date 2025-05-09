/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/09 13:46:31 by timmi            ###   ########.fr       */
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

void	cmd_execution(char **argv)
{
	char	*cmd_path;
	
	cmd_path = pathfinder(argv[0]);
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
}

int	ft_extern(t_shell *s)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == 0)
		cmd_execution(s->root_node->data.ast_exec.argv);
	waitpid(pid1, NULL, 0);
	return (1);
}

int	simple_cmd(t_shell *s)
{
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], CD, ft_strlen(CD)) == 0)
		return (ft_cd(s));
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], ECHO, ft_strlen(ECHO)) == 0)
		return (ft_echo(s, 0));
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], PWD, ft_strlen(PWD)) == 0)
		return (ft_pwd(s, 0));
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], ENV, ft_strlen(ENV)) == 0)
		return (ft_env(s, 0));
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], UNSET, ft_strlen(UNSET)) == 0)
		return (ft_unset(s));
	if (ft_strncmp(s->root_node->data.ast_exec.argv[0], EXPORT, ft_strlen(EXPORT)) == 0)
		return (ft_export(s));
	return (ft_extern(s));
}
