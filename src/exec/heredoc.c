/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/06 18:41:32 by emonacho         ###   ########.fr       */
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

// 🚧 DELIMITER -> doit etre une 'str', si celle-ci commence et fini par des quotes, l'expansion de variable est desactivee. 🚧
// 🚧 DELIMITER -> si il est appele entre quotes, son appel final n'a pas besoin de l'etre. 🚧
int	is_delimiter(char *line, char *delimiter)	// 🚨 A TESTER!
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
			|| delimiter[j] == '\''|| delimiter[j] == '\"'))
			return (1);
	}
	return (0);
}

int	write_heredoc(t_shell *s, char *delimiter, int to_expand)
{
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, delimiter))
			break ;
		if (to_expand == 1)
		{
			if ((delimiter[0] != '\'' && delimiter[ft_strlen(delimiter)] != '\'')		// 🚨 A TESTER!
				&& (delimiter[0] != '\"' && delimiter[ft_strlen(delimiter)] != '\"'))	// 🚨 A TESTER!
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
	while (node->data.exec.heredoc_list[i] && i < node->data.exec.heredoc_count)
	{
		printf("%shandle_heredoc | current delimiter: %s%s\n", P, node->data.exec.heredoc_list[i], RST);	// 🖨️PRINT💥DEBUGING
		if (fd_in > 0)
			if (close(fd_in) < 0)
				return (-1);
		s->fd = 0;
		if (i == node->data.exec.heredoc_count - 1)
		{
			if (write_heredoc(s, node->data.exec.heredoc_list[i], 1) != 0)
				return (-1);
		}
		else
			if (write_heredoc(s, node->data.exec.heredoc_list[i], 0) != 0)
				return (-1);
		fd_in = redir_in(s->heredoc_tmp, 0);
		if (fd_in < 0)
			return (-1);
		i++;
	}
	return (fd_in);
}
