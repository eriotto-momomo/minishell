/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/16 14:58:18 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_nested_heredoc(void)
{
	return (0);
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

void	reset_prompt(t_shell *s, int mode)
{
	(void)s;

	rl_on_new_line();
	rl_replace_line("", 0);
	if (mode == RESET_PROMPT)
		rl_redisplay();
	if (mode == HEREDOC_PROMPT)
		return ;
		//s->line = readline(">");
}

// 0. 'node->data.ast_redir.filename' is the delimiter
// 1. OPEN the heredoc and display a new prompt begining by '>'
// 2. Handle multiple nested HEREDOC
// ...

// NE DOIT PAS METTRE A JOUR HISTORY?!
int	handle_heredoc(t_shell *s)
{
	printf("%sHEREDOC work in progress ...%s\n", P, RST);

	char	*delimiter;

	delimiter = ft_strdup(s->root_node->data.ast_redir.filename);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (s->line && *s->line)
		{
			if (is_delimiter(s->line, delimiter))
				break ;
			//if (is_nested_heredoc)
			//{
			//}
		}
		free(s->line);
	}
	return (-1);
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
		fd = handle_heredoc(s);
	else
		fd = w_open_redir(s->root_node);
	return (fd);
}
