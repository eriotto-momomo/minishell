/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .pipe_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:16:08 by timmi             #+#    #+#             */
/*   Updated: 2025/07/25 15:42:04 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	close_pipes(t_ast *node, int pipe_fd[][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe_fd[i][0] != -1
			&& pipe_fd[i][0] != node->data.s_exec.fd_in
			&& pipe_fd[i][0] != node->data.s_exec.fd_out)
		{
			close(pipe_fd[i][0]);
			pipe_fd[i][0] = -1;
		}
		if (pipe_fd[i][1] != -1
			&& pipe_fd[i][1] != node->data.s_exec.fd_in
			&& pipe_fd[i][1] != node->data.s_exec.fd_out)
		{
			close(pipe_fd[i][1]);
			pipe_fd[i][1] = -1;
		}
		i++;
	}
	return (0);
}

int	setup_pipe(int fd_in, int fd_out)
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
	return (0);
}

int	close_fd(t_ast *node)
{
	if (node->tag == EXEC_NODE)
	{
		if (f_close(&node->data.s_exec.fd_in) != 0)
			return (1);
		if (f_close(&node->data.s_exec.fd_out) != 0)
			return (1);
		return (0);
	}
	else if (node->tag == PIPE_NODE)
	{
		if (close_fd(node->data.s_pipe.left) != 0)
			return (1);
		if (close_fd(node->data.s_pipe.right) != 0)
			return (1);
	}
	return (0);
}
