/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/26 11:53:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(t_shell *s, t_ast *node)
{
	int	i;

	s->heredoc_fd = 0;
	i = -1;
	while (++i < node->data.s_exec.heredoc_count)
	{
		if (s->heredoc_fd > 0)
			if (close(s->heredoc_fd) < 0)
				return (-1);
		s->fd = 0;
		if (i == node->data.s_exec.heredoc_count - 1)
		{
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 1) != 0)
				return (-1);
		}
		else
		{
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 0) != 0)
				return (-1);
		}
		s->heredoc_fd = redir_in(s, s->heredoc_tmp, 0);
		w_free((void **)&s->line);
		if (s->heredoc_fd < 0)
			return (-1);
	}
	return (0);
}

int	write_heredoc(t_shell *s, char *del, int to_expand)
{
	if (open_heredoc(s) < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		if (g_sig != 0)
			break ;
		s->line = readline("> ");
		if (!s->line)
			break ;
		if (is_delimiter(s->line, del))
			break ;
		if (to_expand == 1)
			if ((del[0] != '\'' && del[ft_strlen(del) - 1] != '\'')
				&& (del[0] != '\"' && del[ft_strlen(del) - 1] != '\"'))
				expand(s->numerr, s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	if (close(s->fd) < 0)
		return (-1);
	return (0);
}

int	handle_heredoc(t_shell *s, t_ast *node)
{
	if (handle_termios(s, 0) != 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	s->heredoc_pid = fork();
	if (s->heredoc_pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (s->heredoc_pid == 0)
	{
		if (close_fd(node) != 0 || close_pipes(node, s->pipe_fd, s->pipe_count) != 0)
			return (-1);
		setup_signals(s, HEREDOC_SIGNALS);
		if (heredoc_loop(s, node) == -1)
			kill_children(s);
		clean_free(s);
		if (g_sig == SIGINT)
			exit(130);
		exit(s->numerr);
	}
	waitheredoc(&s->numerr, s->heredoc_pid);
	if (handle_termios(s, 1) != 0)
		return (-1);
	s->heredoc_fd = open(HEREDOC_FILE_PATH, O_RDONLY);
	setup_signals(s, DEFAULT_SIGNALS);
	return (s->heredoc_fd);
}

void	waitheredoc(uint8_t *numerr, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		*numerr = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		*numerr = WEXITSTATUS(status);
	else
		*numerr = 1;
}
