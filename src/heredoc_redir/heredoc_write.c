/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:29:53 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/26 20:17:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	put_in_heredoc(char *line, int fd)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	if (!new_line)
		return (1);
	ft_putstr_fd(new_line, fd);
	free(new_line);
	return (0);
}

static int	is_eof(char *line, char *delimiter)
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

static int	heredoc_loop(t_shell *s, char *eof, int index, int count)
{
	while (1)
	{
		if (g_sig != 0)
			break ;
		s->line = readline("> ");
		if (!s->line)
			break ;
		if (is_eof(s->line, eof))
			break ;
		if (index == count - 1)
			if ((eof[0] != '\'' && eof[ft_strlen(eof) - 1] != '\'')
				&& (eof[0] != '\"' && eof[ft_strlen(eof) - 1] != '\"'))
				expand(s->numerr, s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->heredoc_fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	return (0);
}

int	write_heredoc(t_shell *s, t_ast *node)
{
	int	i;

	i = 0;
	while (i < node->data.s_exec.heredoc_count)
	{
		s->heredoc_fd = open(HEREDOC_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (s->heredoc_fd < 0)
			return (-1);
		reset_prompt(s, HEREDOC_PROMPT);
		if (heredoc_loop(s, node->data.s_exec.heredoc_list[i],
				i, node->data.s_exec.heredoc_count) != 0)
			return (-1);
		if (close(s->heredoc_fd) < 0)
			return (-1);
		i++;
	}
	s->heredoc_fd = open(HEREDOC_FILE_PATH, O_RDONLY);
	if (s->heredoc_fd < 0)
		return (print_error(&s->numerr, errno));
	return (s->heredoc_fd);
}
