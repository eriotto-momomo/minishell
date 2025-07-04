/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:53 by timmi             #+#    #+#             */
/*   Updated: 2025/07/04 20:15:43 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_heredoc(t_shell *s, t_ast *node)
{
	if (!node)
		return (0);
	if (node->tag == EXEC_NODE)
	{
		if (node->data.s_exec.path_tmp_file)
			write_heredoc(s, node->data.s_exec.path_tmp_file, node->data.s_exec.eof_list, node->data.s_exec.eof_count);
	}
	else if (node->tag == PIPE_NODE)
	{
		process_heredoc(s, node->data.s_pipe.left);
		process_heredoc(s, node->data.s_pipe.right);
	}
	return (0);
}

static int	fork_heredoc(t_shell *s)
{
	pid_t	heredoc_pid;
	int		status;

	status = 0;
	heredoc_pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
	s->child_exit = 1;
	if (heredoc_pid == 0)
	{
		setup_signals(s, HEREDOC_SIGNALS);
		process_heredoc(s, s->current_node);
		close_fd(s->root_node);
		kill_children(s);
	}
	waitpid(heredoc_pid, &status, 0);
	if (WIFEXITED(status))
		s->numerr = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->numerr = WTERMSIG(status);
	setup_signals(s, DEFAULT_SIGNALS);
	return (0);
}

int	fill_heredocs(t_shell *s)
{
	fork_heredoc(s);
	return (0);
}
