/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:16:08 by timmi             #+#    #+#             */
/*   Updated: 2025/07/25 15:46:38 by emonacho         ###   ########.fr       */
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

void	close_pipes(int count, int pipe_fd[][2])
{
	int	i;
	int	tmp;

	tmp = errno;
	i = -1;
	while (++i < count)
	{
		//fprintf(stderr, "%sclose_pipes | pipe_fd[%d][0]: %d | pipe_fd[%d][1]: %d%s\n", C, i, pipe_fd[i][0], i, pipe_fd[i][1], RST);
		if (is_open(pipe_fd[i][0]))
			close(pipe_fd[i][0]);
		if (is_open(pipe_fd[i][1]))
			close(pipe_fd[i][1]);
	}
	if (errno != tmp)
		errno = tmp;
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
