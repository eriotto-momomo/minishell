/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:29:53 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/24 20:52:02 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	put_in_heredoc(char *line, int fd)
{
	char	*new_line;

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

static int	is_eof(char *line, char *delimiter)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (delimiter[j] && ft_isquote(delimiter[j]))
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

static int	heredoc_loop(t_shell *s, char *eof, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (g_sig == SIGINT)
		{
			s->numerr = 130;
			break ;
		}
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_eof(line, eof))
			break ;
		// 🚩 A tester: '"
		// 🚩 A tester: '''''"
		// 🚩 A tester: '"""
		// 🚩 A tester: a chaque fois qu'on a un nombre impair de '\'' suivi d'un '\"' ->> invalid read of 1

		// V1
		//if ((eof[0] != '\'' && eof[ft_strlen(eof) - 1] != '\'')
		//	&& (eof[0] != '\"' && eof[ft_strlen(eof) - 1] != '\"'))
		//	expand(s->numerr, s->env_list, &(line));
		////////

		// V2
		if ((eof[0] != '\'' && eof[ft_strlen(eof) - 1] != '\'')
			&& (eof[0] != '\"' && eof[ft_strlen(eof) - 1] != '\"'))
			expand_heredoc(s->numerr, s->env_list, &(line));
		/////////////

		if (put_in_heredoc(line, fd) != 0)
			return (-1);
		w_free((void **)&line);
	}
	w_free((void **)&line);
	return (0);
}

int	write_heredoc(t_shell *s, char *path, char **eof_list, int eof_count)
{
	int	i;
	int	heredoc_fd;

	heredoc_fd = -1;
	i = 0;
	while (i < eof_count)
	{
		heredoc_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (heredoc_fd < 0)
			return (-1);
		reset_prompt(s, HEREDOC_PROMPT);
		if (heredoc_loop(s, eof_list[i], heredoc_fd) != 0)
		{
			if (close(heredoc_fd) < 0)
				return (-1);
			return (-1);
		}
		if (close(heredoc_fd) < 0)
			return (-1);
		i++;
	}
	return (0);
}
