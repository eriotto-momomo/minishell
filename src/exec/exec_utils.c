/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/05 19:18:27 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//🚨 V2 Work in progress
int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	**env_table;
	char	*path;

	path = path_making(env, argv[0]);
	if (!path)
		print_custom_error(&s->numerr, 127, "Command not found");
	if (path)
	{
		env_table = ltotable(env);
		if (!env_table)
		{
			w_free((void **)&path);
			print_error(&s->numerr, ENOMEM);
		}
	}
	if (path && env_table)
	{
		if (execve(path, argv, env_table) == -1)
		{
			w_free((void **)&path);
			ft_free_char_array(env_table, count_var(env));
			print_custom_error(&s->numerr, 126, strerror(errno));
		}
	}
	//kill_children(s); //🚨 Fais apres la fonction
	return (0);
}

//int	cmd_execution(t_shell *s, t_env *env, char **argv)
//{
//	char	**env_table;
//	char	*path;

//	//close_pipes(s->pipe_count, s->pipe_fd);	//🚨
//	path = path_making(env, argv[0]);
//	if (!path)
//	{
//		close_fds(s->root_node);
//		print_custom_error(&s->numerr, 127, "Command not found");
//		kill_children(s);
//	}
//	env_table = ltotable(env);
//	if (!env_table)
//	{
//		close_fds(s->root_node);
//		w_free((void **)&path);
//		print_error(&s->numerr, ENOMEM);
//		kill_children(s);
//	}
//	if (execve(path, argv, env_table) == -1)
//	{
//		close_fds(s->root_node);
//		w_free((void **)&path);
//		ft_free_char_array(env_table, count_var(env));
//		print_custom_error(&s->numerr, 126, strerror(errno));
//		kill_children(s);
//	}
//	return (0);
//}

int	waiton(uint8_t *numerr, int *child_pids, int pid_count)
{
	int	i;
	int	status;
	int	pid;

	i = 0;
	while (i < pid_count)
	{
		pid = waitpid(child_pids[i], &status, 0);
		if (pid == -1)
			continue ;
		if (WIFEXITED(status))
			*numerr = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*numerr = WTERMSIG(status);
		i++;
	}
	return (0);
}

int	close_fds(t_ast *node)
{
	if (node->tag == EXEC_NODE)
	{
		if (node->data.s_exec.fd_in > 2 && is_open(node->data.s_exec.fd_in))
			close(node->data.s_exec.fd_in);
		if (node->data.s_exec.fd_out > 2 && is_open(node->data.s_exec.fd_out))
			close(node->data.s_exec.fd_out);
		node->data.s_exec.fd_in = STDIN_FILENO;
		node->data.s_exec.fd_out = STDOUT_FILENO;
		return (0);
	}
	else if (node->tag == PIPE_NODE)
	{
		if (close_fds(node->data.s_pipe.left) != 0)
			return (1);
		if (close_fds(node->data.s_pipe.right) != 0)
			return (1);
	}
	return (0);
}
