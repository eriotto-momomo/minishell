/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 17:25:36 by timmi            ###   ########.fr       */
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

int	write_heredoc(t_shell *s, char *del, int to_expand)
{
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
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
				expand(s->env_list, &(s->line));
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
	int	i;
	int	fd_in;

	fd_in = 0;
	i = 0;
	while (i < node->data.s_exec.heredoc_count)
	{
		if (fd_in > 0)
			if (close(fd_in) < 0)
				return (-1);
		s->fd = 0;
		if (i == node->data.s_exec.heredoc_count - 1)
		{
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 1) != 0)
				return (-1);
		}
		else
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 0) != 0)
				return (-1);
		fd_in = redir_in(s->heredoc_tmp, 0);
		if (fd_in < 0)
			return (-1);
		i++;
	}
	return (fd_in);
}
