/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:29:53 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 00:21:15 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int put_in_heredoc(char *line, int fd)
{
	char *new_line;

	new_line = ft_strjoin(line, "\n");
	if (!new_line)
	{
		w_free((void **)&line);
		return (1);
	}
	ft_putstr_fd(new_line, fd);
	free(new_line);
	return (0);
}

static int is_eof(char *line, char *delimiter)
{
	size_t i = 0;
	size_t j = 0;

	while (delimiter[j] && (delimiter[j] == '\'' || delimiter[j] == '"'))
		j++;
	if (line[i] == delimiter[j])
	{
		while (line[i] && delimiter[j] && line[i] == delimiter[j])
		{
			i++;
			j++;
		}
		if (line[i] == '\0' && (delimiter[j] == '\0' || delimiter[j] == '\'' || delimiter[j] == '"'))
			return (1);
	}
	return (0);
}

static int heredoc_loop(t_shell *s, char *eof, int index, int count, int fd)
{
	char	*line;
	while (1)
	{
		if (g_sig != 0)
			break;
		line = readline("> ");
		if (line)
			break;
		if (is_eof(line, eof))
			break;
		if (index == count - 1)
		{
			if ((eof[0] != '\'' && eof[ft_strlen(eof) - 1] != '\'') &&
				(eof[0] != '"' && eof[ft_strlen(eof) - 1] != '"'))
				expand(s->numerr, s->env_list, &line);
		}
		if (put_in_heredoc(line, fd) != 0)
			return (-1);
		w_free((void **)&line);
	}
	w_free((void **)&line);
	return (0);
}

int write_heredoc(t_shell *s, t_ast *node)
{
	int i = 0;
	int pipe_fd[2];
	int last_fd = -1;

	while (i < node->data.s_exec.heredoc_count)
	{
		if (pipe(pipe_fd) < 0)
			return (-1);
		pid_t pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			close(pipe_fd[0]);
			reset_prompt(s, HEREDOC_PROMPT);
			heredoc_loop(s, node->data.s_exec.heredoc_list[i], i, node->data.s_exec.heredoc_count, pipe_fd[1]);
			close(pipe_fd[1]);
			kill_children(s);
		}
		else
		{
			close(pipe_fd[1]);
			waitpid(pid, NULL, 0);
			if (last_fd != -1)
				close(last_fd);
			last_fd = pipe_fd[0];
		}
		i++;
	}
	s->heredoc_fd = last_fd;
	return (last_fd);
}

