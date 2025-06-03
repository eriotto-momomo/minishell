/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/03 17:16:02 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_output(t_shell *s, t_ast *current_node, int fd_in)
{
	if (current_node->data.ast_redir.mode == OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename,
			O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (current_node->data.ast_redir.mode == APP_OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (s->fd < 0)
		return (-1);
	if ((s->final_output_fd == -1) && s->fd >= 0)
	{
		s->stdout_save = dup(STDOUT_FILENO);
		if (s->stdout_save < 0)
			return (-1);
		s->final_output_fd = s->fd;
	}
	if (s->final_output_fd > -1 && s->fd != s->final_output_fd)
		if (close(s->fd) < 0)
			return (-1);
	if (preorder_exec(s, &current_node->data.ast_redir.left,
			fd_in, s->final_output_fd) != 0)
		return (-1);
	if (s->final_output_fd >= 0)
		if (close(s->final_output_fd) < 0)
			return (-1);
	return (0);
}

int	redirect_input(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	printf("redirect_input |[1]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);	// 🖨️PRINT💥DEBUGING
	if (current_node->data.ast_redir.mode == HERE_DOC)
	{
		if (handle_heredoc(s, current_node, fd_in, fd_out) != 0)
			return (-1);
	}
	else
	{
		printf("redirect_input | %scurrent_node%s\n", Y, RST);	// 🖨️PRINT💥DEBUGING
		print_node(current_node);								// 🖨️PRINT💥DEBUGING

		// 1. Descendre jusqu'a l'exec en ouvrant tous les fd
		// 2. Executer tous les fd (de gauche a droite) avec l'exec node
		// 3. A chaque fd `executé` close le fd

		s->fd = open(current_node->data.ast_redir.filename, O_RDONLY);
		if (s->fd < 0)
			return (-1);
		printf("redirect_input | filename[%s%s%s] open with %ss->fd: %d%s\n", B, current_node->data.ast_redir.filename, RST, Y, s->fd, RST);
		//if (current_node->data.ast_redir.left->tag == AST_REDIR)
		//{
		//	if (handle_redir(s, &current_node->data.ast_redir.left,	// 🚨 RISQUE D'OUVERTURE DE FD MULTIPLES? PREFERER redirect_input/output DIRECTEMENT?🚨
		//		s->fd, fd_out) != 0)
		//		return (-1);
		//}
		//if (preorder_exec(s, &current_node->data.ast_redir.left, s->fd, fd_out) != 0)
		//	return (-1);
	}
	if(close(s->fd) < 0)
		return (-1);
	s->fd = -1;
	//printf("redirect_input | %ss->fd: %d%s\n", Y, s->fd, RST);
	printf("redirect_input |[2]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);	// 🖨️PRINT💥DEBUGING
	return (0);
}
