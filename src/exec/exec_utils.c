/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/13 19:06:32 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_shell *s, t_ast **current_node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (-1);
	if (close_fd((*current_node)) != 0)
		return (1);
	(*current_node)->data.pipe.left->data.exec.fd_out = pipe_fd[1];
	preorder_exec(s, &((*current_node)->data.pipe.left));
	(*current_node)->data.pipe.right->data.exec.fd_in = pipe_fd[0];
	preorder_exec(s, &((*current_node)->data.pipe.right));
	if (close_fd((*current_node)) != 0)
		return (1);
	if (close(pipe_fd[1]) < 0)
		return (1);
	if (close(pipe_fd[0]) < 0)
		return (1);
	return (0);
}

int	handle_exec(t_shell *s, t_ast *node)
{
	if (ft_strncmp(node->data.exec.argv[0], CD, ft_strlen(CD)) == 0)
		return (ft_cd(s->pwd, s->old_pwd, s->home, node));
	if (ft_strncmp(node->data.exec.argv[0], ECHO, ft_strlen(ECHO)) == 0)
		return (ft_echo(&node, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], PWD, ft_strlen(PWD)) == 0)
		return (ft_pwd(s, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], ENV, ft_strlen(ENV)) == 0)
		return (ft_env(s->env_list, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], UNSET, ft_strlen(UNSET)) == 0)
		return (ft_unset(s));
	if (ft_strncmp(node->data.exec.argv[0], EXPORT, ft_strlen(EXPORT)) == 0)
		return (ft_export(&s->env_list, node->data.exec.argc, node->data.exec.argv, node->data.exec.fd_out));
	return (ft_external(s, s->env_list, node));
}

int	setup_pipe(int	fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (-1);
		if (close(fd_in) < 0)
			return (-1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (-1);
		if (close(fd_out) < 0)
			return (-1);
	}
	return (0);
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
