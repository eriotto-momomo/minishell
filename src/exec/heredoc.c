/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/30 12:39:24 by emonacho         ###   ########.fr       */
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

int	write_heredoc(t_shell *s, t_ast *current_node)
{
	char	*ptr;

	printf("%swrite_heredoc | current delimiter%s %s\n", P, RST, current_node->data.ast_redir.filename);
	ptr = current_node->data.ast_redir.filename;
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, current_node->data.ast_redir.filename))
			break ;
		if ((ptr[0] != '\'' && ptr[ft_strlen(ptr)] != '\'')		// 🚨 A TESTER!
			&& (ptr[0] != '\"' && ptr[ft_strlen(ptr)] != '\"'))	// 🚨 A TESTER!
			expand(s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	if (close(s->fd) < 0)
		return (-1);
	return (0);
}

// BACKUP💾
/*int	write_heredoc(t_shell *s)
{
	char	*ptr;

	ptr = s->root_node->data.ast_redir.filename;
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, s->root_node->data.ast_redir.filename))
			break ;
		if ((ptr[0] != '\'' && ptr[ft_strlen(ptr)] != '\'')		// 🚨 A TESTER!
			&& (ptr[0] != '\"' && ptr[ft_strlen(ptr)] != '\"'))	// 🚨 A TESTER!
			expand(s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	if (close(s->fd) < 0)
		return (-1);
	return (0);
}*/

int	handle_heredoc(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	if (current_node->data.ast_redir.left->tag == AST_EXEC)
		s->root_redir = current_node;
	if (current_node->data.ast_redir.left->data.ast_redir.mode == HERE_DOC)
	{
		if (handle_heredoc(s, current_node->data.ast_redir.left, fd_in, fd_out) < 0)
			return (-1);
	}
	if (write_heredoc(s, current_node) != 0)
		return (-1);
	if (redirect_input(s, &(*s->root_redir)) != 0)
		return (-1);
	printf("%shandle_heredoc | s->root_redir%s\n", P, RST);
	print_node(s->root_redir);
	//if (current_node->data.ast_redir.left->tag == AST_EXEC) // 🚨TEST🚨
	//	preorder_exec(s, &current_node->data.ast_redir.left, fd_in, fd_out);
	return (0);
}
