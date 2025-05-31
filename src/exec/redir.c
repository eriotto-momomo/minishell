/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/31 20:32:01 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	redirect_output(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	printf("redirect_output |[1]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	if (current_node->data.ast_redir.mode == OUT_REDIR)
		fd_out = open(current_node->data.ast_redir.filename,
			O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (current_node->data.ast_redir.mode == APP_OUT_REDIR)
		fd_out = open(current_node->data.ast_redir.filename,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out < 0)
		return (-1);
	if ((s->root_fd == -1) && fd_out >= 0)
		s->root_fd = fd_out;
	if (s->root_fd > -1 && fd_out != s->root_fd)
		if (close(fd_out) < 0)
			return (-1);
	fd_out = 1;									//📍 Probablement useless
	printf("redirect_outputt | %sfd_out: %d%s\n", Y, fd_out, RST);
	if (preorder_exec(s, &current_node->data.ast_redir.left,
			fd_in, s->root_fd) != 0)
		return (-1);
	if (close(s->root_fd) < 0)
		return (-1);
	s->root_fd = -1;
	printf("redirect_output |[2]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	return (0);
}


int	redirect_input(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	printf("redirect_input |[1]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);

	if (current_node->data.ast_redir.mode == HERE_DOC)
		handle_heredoc(s, current_node, fd_in, fd_out);
	else
	{
		printf("redirect_input | %scurrent_node%s\n", Y, RST);
		print_node(current_node);
		s->fd = open(current_node->data.ast_redir.filename, O_RDONLY);
		if (s->fd < 0)
			return (-1);
		printf("redirect_input | %ss->fd: %d%s\n", Y, s->fd, RST);
		if (current_node->data.ast_redir.left->tag == AST_EXEC)
			if (preorder_exec(s, &current_node->data.ast_redir.left,
				s->fd, fd_out) != 0)
				return (-1);
	}
	//if(close(fd_in < 0))
	//	return (-1);
	if(close(s->fd < 0))
		return (-1);
	printf("redirect_input | %ss->fd: %d%s\n", Y, s->fd, RST);
	printf("redirect_input |[2]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	s->fd = -1;
	return (0);
}

// BACKUP 💾
/*int	redirect_input(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	printf("redirect_input |[1]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	s->fd = -1;
	if (current_node->data.ast_redir.mode == HERE_DOC)
		handle_heredoc(s, current_node, fd_in, fd_out);
	else
	{
		printf("redirect_input | %scurrent_node%s\n", Y, RST);
		print_node(current_node);
		s->fd = open(current_node->data.ast_redir.filename, O_RDONLY);
		if (s->fd < 0)
			return (-1);
		printf("redirect_input | %ss->fd: %d%s\n", Y, s->fd, RST);
		if (current_node->data.ast_redir.left->tag == AST_EXEC)
			if (preorder_exec(s, &current_node->data.ast_redir.left,
				s->fd, fd_out) != 0)
				return (-1);
	}
	if(close(s->fd < 0))
		return (-1);
	printf("redirect_input | %ss->fd: %d%s\n", Y, s->fd, RST);
	printf("redirect_input |[2]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	return (0);
}*/

//int	redirect(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
//{
//	printf("%sredirect|[1] fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
//	s->fd = -1;
//	if (current_node->data.ast_redir.mode == HERE_DOC)
//	{
//		printf("redirect| %scurrent_node BEFORE handle_heredoc%s\n", Y, RST);
//		print_node(current_node);
//		s->fd = handle_heredoc(s, current_node, fd_in, fd_out);
//		s->root_redir = NULL;
//		printf("redirect| %scurrent_node AFTER handle_heredoc%s\n", Y, RST);
//		print_node(current_node);
//	}
//	//else if (current_node->data.ast_redir.mode == IN_REDIR)
//	//	s->fd = redirect_input(s, current_node);
//	if (s->fd < 0)
//		return (-1);
//	printf("%sredirect|[2] fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
//	return (s->fd);
//}
// 🚩 Le FD des OUT_REDIR est a 'close' apres les redirections 🚩
