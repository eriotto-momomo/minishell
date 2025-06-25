/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/25 12:02:13 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_in_heredoc(char *line, int fd)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	if (!new_line)
		return (1);
	ft_putstr_fd(new_line, fd);
	free(new_line);
	return (0);
}

int	is_delimiter(char *line, char *delimiter)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (delimiter[j] && (delimiter[j] == '\'' || delimiter[j] == '\"'))
		j++;
	if (line[i] == delimiter[j])
	{
		while (line[i] && delimiter[j]
			&& (line[i] == delimiter[j]))
		{
			i++;
			j++;
		}
		if (line[i] == '\0' && (delimiter[j] == '\0'
				|| delimiter[j] == '\'' || delimiter[j] == '\"'))
			return (1);
	}
	return (0);
}

int	open_heredoc(t_shell *s)
{
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		terminate_shell(s);
	return (s->fd);
}

int	write_heredoc(t_shell *s, char *del, int to_expand)
{
	if (open_heredoc(s) < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break ;
		if (is_delimiter(s->line, del))
			break ;
		if (to_expand == 1)
		{
			if ((del[0] != '\'' && del[ft_strlen(del) - 1] != '\'')
				&& (del[0] != '\"' && del[ft_strlen(del) - 1] != '\"'))
				expand(s->numerr, s->env_list, &(s->line));
		}
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
	pid_t	heredoc_pid;

	setup_signals(s, HEREDOC_SIGNALS);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	heredoc_pid = fork();
	if (heredoc_pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (heredoc_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (heredoc_loop(s, node) == -1)
			kill_children(s);
		clean_free(s);
		exit(0);
	}
	waitheredoc(&s->numerr, heredoc_pid);
	setup_signals(s, DEFAULT_SIGNALS);
	s->heredoc_fd = redir_in(s, s->heredoc_tmp, 0);
	return (s->heredoc_fd);
}
