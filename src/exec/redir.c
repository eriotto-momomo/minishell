/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/15 18:56:36 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc(t_ast *node)
{
	printf("%sHEREDOC work in progress ...%s\n", P, RST);
	printf("handle_heredoc | %sdelimiter = %s%s\n", P, node->data.ast_redir.filename, RST);

	// 0. 'node->data.ast_redir.filename' is the delimiter
	// 1. OPEN the heredoc and display a new prompt begining by '>'
	// 2.
	// ...

	// NE DOIT PAS METTRE A JOUR HISTORY?!

	return (-1);
}

// '>'	fd = 1, O_CREAT | O_WRONLY |  O_TRUNC	-> mode = 1 (redir output)(creating / overwriting)
// '>>'	fd = 1, O_CREAT | O_WRONLY | O_APPEND	-> mode = 2 (redir output)(appending)
// '<'	fd = 0, O_RDONLY						-> mode = 3 (redir input)(reading)
// '<<'	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
int	w_open_redir(t_ast *node)
{
	int	fd;

	fd = -1;
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

int	get_fd(t_ast *node)
{
	int	fd;

	fd = -1;
	if (node->tag == AST_REDIR)
		printf("test_redir | %sAST_REDIR found!%s\n", G, RST);
	else {
		printf("test_redir | %sNo AST_REDIR found!%s\n", R, RST);
		return (0); }
	if (node->data.ast_redir.mode == HERE_DOC)
		fd = handle_heredoc(node);
	else
		fd = w_open_redir(node);
	return (fd);
}
