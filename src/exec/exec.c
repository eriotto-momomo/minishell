/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/20 20:15:26 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int close_fd(t_ast *node)
{
	if(node->tag == EXEC_NODE)
	{
		if (node->data.exec.fd_in > 2)
			if (close(node->data.exec.fd_in) != 0)
				return (1);
		if (node->data.exec.fd_out > 2)
			if (close(node->data.exec.fd_out) != 0)
				return (1);
	}
	else if(node->tag == PIPE_NODE)
	{
		if (close_fd(node->data.pipe.left) != 0)
			return (1);
		if (close_fd(node->data.pipe.right) != 0)
			return (1);
	}
	node->data.exec.fd_in = 0;
	node->data.exec.fd_out = 1;
	return (0);
}

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE, "fork"));
	if (pid == 0)
	{
		if (setup_pipe(node->data.exec.fd_in, node->data.exec.fd_out) == -1)
			return (print_error(&s->numerr, errno, "setup_pipe"));
		while (++i < s->pipe_count)
		{
			if (s->pipe_fd[i][0] != node->data.exec.fd_in
				&& s->pipe_fd[i][0] != node->data.exec.fd_out)
				close(s->pipe_fd[i][0]);
			if (s->pipe_fd[i][1] != node->data.exec.fd_in
				&& s->pipe_fd[i][1] != node->data.exec.fd_out)
				close(s->pipe_fd[i][1]);
		}
		cmd_execution(s, env, node->data.exec.argv);
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
		if ((*node)->data.exec.heredoc_count > 0)
			(*node)->data.exec.fd_in = handle_heredoc(s, (*node));
		if (string_processing(s, &(*node)->data.exec.argc, &(*node)->data.exec.argv) != 0)
			return (1);
		if((*node)->data.exec.argc > 0)
			if (handle_exec(s, (*node)) != 0)
				return (1);
	}
	return (0);
}

int	execution(t_shell *s)
{
	int	i;
	int	status;

	i = 0;
	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		return (print_error(&s->numerr, ENOMEM, "ft_strdup"));
	setup_signals(s, DEFAULT_SIGNALS);
	if (preorder_exec(s, &s->current_node) != 0)
		return (1);
	while (i < s->pid_count)
	{
		waitpid(s->child_pids[i], &status, 0);
		if (g_status == CLEAN_EXIT)
		{
			if (kill(s->child_pids[i], SIGKILL) < 0)
				return (print_error(&s->numerr, errno, "kill"));
			break;
		}
		i++;
	}
	free_ast(&(s->root_node));
	unlink(HEREDOC_FILE_PATH);
	w_free((void **)&s->heredoc_tmp);
	return (0);
}


