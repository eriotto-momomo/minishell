/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:08:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/26 16:55:23 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_pipes(t_ast *node, int pipe_fd[][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe_fd[i][0] != -1
			&& pipe_fd[i][0] != node->data.s_exec.fd_in
			&& pipe_fd[i][0] != node->data.s_exec.fd_out)
		{
			close(pipe_fd[i][0]);
			pipe_fd[i][0] = -1;
		}
		if (pipe_fd[i][1] != -1
			&& pipe_fd[i][1] != node->data.s_exec.fd_in
			&& pipe_fd[i][1] != node->data.s_exec.fd_out)
		{
			close(pipe_fd[i][1]);
			pipe_fd[i][1] = -1;
		}
		i++;
	}
	return (0);
}

static void	process_pipe_node(t_shell *s, t_ast **node, int cur_pipe)
{
	t_ast	*right;

	right = (*node)->data.s_pipe.left->data.s_pipe.right;
	if (right->tag == EXEC_NODE
		&& right->data.s_exec.fd_out == STDOUT_FILENO)
		right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
}

int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe;
	int		dup_read;

	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, NULL, errno));
	if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
		process_pipe_node(s, node, cur_pipe);
	else if ((*node)->data.s_pipe.left->tag == EXEC_NODE
		&& (*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
		(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
	dup_read = dup(s->pipe_fd[cur_pipe][0]);
	if (dup_read < 0)
		return (print_error(&s->numerr, NULL, errno));
	if ((*node)->data.s_pipe.right->data.s_exec.fd_in == STDIN_FILENO)
		(*node)->data.s_pipe.right->data.s_exec.fd_in = dup_read;
	else
		close(dup_read);
	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));
	(*node)->data.s_pipe.right->data.s_exec.fd_in = -1;
	close_pipes((*node), s->pipe_fd, s->pipe_count);
	return (0);
}

int	setup_pipe(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (1);
		if (close(fd_in) < 0)
			return (1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (1);
		if (close(fd_out) < 0)
			return (1);
	}
	return (0);
}
