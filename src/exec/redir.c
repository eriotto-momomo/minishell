/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/30 12:39:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_input(t_shell *s, t_ast *current_node)
{
	if (current_node->data.ast_redir.mode == IN_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_RDONLY);
	else if (current_node->data.ast_redir.mode == HERE_DOC)
		s->fd = open(s->heredoc_tmp, O_RDONLY);
	if (s->fd < 0)
		return (-1);
	if (close(s->fd) < 0)
		return (-1);
	if (current_node->data.ast_redir.mode == IN_REDIR
			&& current_node->data.ast_redir.left->tag == AST_EXEC)
		current_node->data.ast_redir.left->data.ast_exec.argv
		[current_node->data.ast_redir.left->data.ast_exec.argc] =
			ft_strdup(current_node->data.ast_redir.filename);
	else if (current_node->data.ast_redir.mode == HERE_DOC
			&& current_node->data.ast_redir.left->tag == AST_EXEC)
		current_node->data.ast_redir.left->data.ast_exec.argv
		[current_node->data.ast_redir.left->data.ast_exec.argc] =
			ft_strdup(s->heredoc_tmp);
	if (!current_node->data.ast_redir.left->data.ast_exec.argv
		[current_node->data.ast_redir.left->data.ast_exec.argc])
		return (-1);
	printf("%sredirect_input | current_node%s\n", P, RST);
	print_node(current_node);
	return (0);
}

// BACKUP💾
/*int	redirect_input(t_shell *s)
{
	if (s->root_node->data.ast_redir.mode == IN_REDIR)
		s->fd = open(s->root_node->data.ast_redir.filename, O_RDONLY);
	else if (s->root_node->data.ast_redir.mode == HERE_DOC)
		s->fd = open(s->heredoc_tmp, O_RDONLY);
	if (s->fd < 0)
		return (-1);
	if (close(s->fd) < 0)
		return (-1);
	if (current_node->data.ast_redir.left->tag == AST_EXEC)
		current_node->data.ast_redir.left->data.ast_exec.argv[current_node->data.ast_redir.left->data.ast_exec.argc] = ft_strdup(s->heredoc_tmp);
	return (0);
}*/

int	redirect(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	s->fd = -1;
	if (current_node->data.ast_redir.mode == HERE_DOC)
	{
		s->fd = handle_heredoc(s, current_node, fd_in, fd_out);
		s->root_redir = NULL;
	}
	else if (current_node->data.ast_redir.mode == IN_REDIR)
		s->fd = redirect_input(s, current_node);
	else if (current_node->data.ast_redir.mode == OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (current_node->data.ast_redir.mode == APP_OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (s->fd < 0)
		return (-1);
	return (s->fd);
}

// BACKUP💾
/*int	redirect(t_shell *s, t_ast *current_node)
{
	s->fd = -1;
	if (current_node->data.ast_redir.mode == IN_REDIR
		|| current_node->data.ast_redir.mode == HERE_DOC)
	{
		if (current_node->data.ast_redir.mode == HERE_DOC)
		{
			if (current_node->data.ast_redir.left->data.ast_redir.mode == HERE_DOC)
			{
				if (redirect(s, s->current_node->data.ast_redir.left) < 0)
					return (-1);
			}
			//printf("redirect| %scurrent_node:%s\n", Y, RST);
			//print_node(current_node);
			if (handle_heredoc(s, current_node) != 0)
				return (-1);
		}
		s->fd = redirect_input(s, current_node);
		w_free((void**)&s->heredoc_tmp);
	}
	else if (current_node->data.ast_redir.mode == OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (current_node->data.ast_redir.mode == APP_OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (s->fd < 0)
		return (-1);
	return (s->fd);
}*/
// 🚩 Le FD des OUT_REDIR est a 'close' apres les redirections 🚩
