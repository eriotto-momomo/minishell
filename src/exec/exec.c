/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/24 10:27:13 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_fd(t_ast *node)
{
	if (node->tag == EXEC_NODE)
	{
		if (node->data.s_exec.fd_in > 2)
			if (close(node->data.s_exec.fd_in) != 0)
				return (1);
		if (node->data.s_exec.fd_out > 2)
			if (close(node->data.s_exec.fd_out) != 0)
				return (1);
	}
	else if (node->tag == PIPE_NODE)
	{
		if (close_fd(node->data.s_pipe.left) != 0)
			return (1);
		if (close_fd(node->data.s_pipe.right) != 0)
			return (1);
	}
	node->data.s_exec.fd_in = 0;
	node->data.s_exec.fd_out = 1;
	return (0);
}

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			return (print_error(&s->numerr, errno));
		while (++i < s->pipe_count)
		{
			if (s->pipe_fd[i][0] != node->data.s_exec.fd_in
				&& s->pipe_fd[i][0] != node->data.s_exec.fd_out)
				close(s->pipe_fd[i][0]);
			if (s->pipe_fd[i][1] != node->data.s_exec.fd_in
				&& s->pipe_fd[i][1] != node->data.s_exec.fd_out)
				close(s->pipe_fd[i][1]);
		}
		cmd_execution(s, env, node->data.s_exec.av);
	}
	else
		s->child_pids[s->pid_count++] = pid;
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **node)
{
	if (!(*node))
		return (0);
	if ((*node)->tag == PIPE_NODE)
	{
		if (handle_pipe(s, &(*node)) != 0)
			return (1);
	}
	else if ((*node)->tag == EXEC_NODE)
	{
		if ((*node)->data.s_exec.heredoc_count > 0)
			(*node)->data.s_exec.fd_in = handle_heredoc(s, (*node));
		if (string_processing(s, &(*node)->data.s_exec.ac,
				&(*node)->data.s_exec.av) != 0)
			return (1);
		if ((*node)->data.s_exec.ac > 0)
			if (handle_exec(s, (*node)) != 0)
				return (1);
	}
	close_fd((*node));
	return (0);
}

static int	waiton(uint8_t *numerr, int *child_pids, int pid_count)
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

int	execution(t_shell *s)
{
	int	i;

	i = 0;
	setup_signals(s, DEFAULT_SIGNALS);
	if (preorder_exec(s, &s->current_node) != 0)
		return (1);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
	{
		while (i < s->pid_count)
		{
			if (kill(s->child_pids[i], SIGKILL) != 0)
				return (print_error(&s->numerr, errno));
			i++;
		}
	}
	waiton(&s->numerr, s->child_pids, s->pid_count);
	free_ast(&(s->root_node));
	unlink(HEREDOC_FILE_PATH);
	return (0);
}
