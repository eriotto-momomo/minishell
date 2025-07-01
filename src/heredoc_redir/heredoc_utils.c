/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:53 by timmi             #+#    #+#             */
/*   Updated: 2025/07/01 18:29:07 by emonacho         ###   ########.fr       */
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

	heredoc_pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_pid == 0)
	{
		g_sig = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		process_heredoc(s, s->current_node);
		//fprintf(stderr, "%sfork_heredoc | 1 | g_sig; %d | s->numerr: %d | s->line: %s%s\n", G, g_sig, s->numerr, s->line, RST);
		close_fd(s->root_node);
		free_ast(&s->root_node);
		w_free((void **)&s->tmp_files_list);
		kill_children(s);
	}
	waitpid(heredoc_pid, NULL, 0);
	setup_signals(s, DEFAULT_SIGNALS);
	//fprintf(stderr, "%sfork_heredoc | 2 | g_sig; %d | s->numerr: %d | s->line: %s%s\n", G, g_sig, s->numerr, s->line, RST);
	//fprintf(stderr, "%sfork_heredoc | EXIT FUNCTION!%s\n", G, RST);
	return (0);
}

int	fill_heredocs(t_shell *s)
{
	fork_heredoc(s);
	//reset_prompt(s, RESET_PROMPT);
	return (0);
}
