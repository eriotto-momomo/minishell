/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/04 10:54:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			exit(print_error(&s->numerr, errno));
		cmd_execution(s, env, node->data.s_exec.av);
	}
	else
	{
		s->child_pids[s->pid_count++] = pid;
		if (node->data.s_exec.fd_in != STDIN_FILENO)
			close(node->data.s_exec.fd_in);
	}
	return (0);
}

int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	**env_table;
	char	*path;

	path = path_making(env, argv[0]);
	if (!path)
	{
		w_free((void **)&path);
		print_custom_error(&s->numerr, 127, "Command not found");
		kill_children(s);
	}
	env_table = ltotable(env);
	if (!env_table)
	{
		w_free((void **)&path);
		print_error(&s->numerr, ENOMEM);
		kill_children(s);
	}
	if (execve(path, argv, env_table) == -1)
	{
		w_free((void **)&path);
		ft_free_char_array(env_table, count_var(env));
		print_custom_error(&s->numerr, 126, strerror(errno));
		kill_children(s);
	}
	return (0);
}

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
