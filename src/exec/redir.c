/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/17 15:27:34 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_in_heredoc(char *line, int fd)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	if (!new_line)
		return (0);
	ft_putstr_fd(new_line, fd);
	free(new_line);
	return (1);
}

int	is_delimiter(char *line, char *delimiter)
{
	size_t	i;

	i = 0;
	if (line[i] == delimiter[i])
	{
		while (line[i] && delimiter[i]
			&& (line[i] == delimiter[i]))
			i++;
		if (line[i] == '\0' && delimiter[i] == '\0')
			return (1);
	}
	return (0);
}

int	handle_heredoc(t_shell *s)
{
	int	fd;

	s->heredoc_tmp = ft_strdup("heredoc_tmp.txt");
	fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (0);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, s->root_node->data.ast_redir.filename))
			break ;
		if (s->root_node->data.ast_redir.filename[0] == '\'')
			expand(s->env_list, &(s->line));
		if (!put_in_heredoc(s->line, fd))
			return (0);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	close(fd);
	return (1);
}


int	w_open_redir(t_ast *node)
{
	int	fd;

	fd = -1;
	if (node->tag != AST_REDIR)
		return (-1);
	if (node->data.ast_redir.mode == OUT_REDIR)
		fd = open(node->data.ast_redir.filename, O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (node->data.ast_redir.mode == APP_OUT_REDIR)
		fd = open(node->data.ast_redir.filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->data.ast_redir.mode == IN_REDIR)
		fd = open(node->data.ast_redir.filename, O_RDONLY);
	if (fd < 0)
	{
		errno = ENOENT;
		ft_puterror("w_open_redir", strerror(errno));
		return (-1);
	}
	return (fd);
}

int	redirect(t_shell *s)
{
	int	fd;

	fd = -1;
	if (s->root_node->data.ast_redir.mode == HERE_DOC)
	{
		if (!handle_heredoc(s))
			return (-1);
	}
	else
		fd = w_open_redir(s->root_node);
	return (fd);
}
// 🚩 FD est a 'close' apres les redirections 🚩
