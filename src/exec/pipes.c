/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:08:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/05 16:32:11 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(int count, int pipe_fd[][2])
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (is_open(pipe_fd[i][0]))
			close(pipe_fd[i][0]);
		if (is_open(pipe_fd[i][1]))
			close(pipe_fd[i][1]);
	}
}

//int	dupto_pipeline(int old_fd, int new_fd, int pipe_fd[][2])
//{

//}

// V2.2
int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe;
	t_ast	*right;

	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, errno));
	//fprintf(stderr, "%shandle_pipe | pipe_in[1]: %d | pipe_out[0]: %d%s\n", Y, s->pipe_fd[s->pipe_count][1], s->pipe_fd[s->pipe_count][0], RST);
	//fprintf(stderr, "handle_pipe | CURRENT NODE(before):\n");
	//print_node((*node));
	if ((*node)->data.s_pipe.right->data.s_exec.fd_in == STDIN_FILENO)
		(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
	else if ((*node)->data.s_pipe.right->data.s_exec.fd_in != STDIN_FILENO)
	{
		dup2((*node)->data.s_pipe.right->data.s_exec.fd_in, s->pipe_fd[cur_pipe][0]);
		if ((*node)->data.s_pipe.right->data.s_exec.fd_in > 2)
			close((*node)->data.s_pipe.right->data.s_exec.fd_in);
		(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
		//fprintf(stderr, "%sdup2! fd_in\n%s", Y, RST);
	}
	if ((*node)->data.s_pipe.left->tag == EXEC_NODE)
	{
		if ((*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
			(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
		else if ((*node)->data.s_pipe.left->data.s_exec.fd_out != STDOUT_FILENO)
		{
			dup2((*node)->data.s_pipe.left->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1]);
			if ((*node)->data.s_pipe.left->data.s_exec.fd_out > 2)
				close((*node)->data.s_pipe.left->data.s_exec.fd_out);
			(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
			//fprintf(stderr, "%sdup2! fd_out - pipe_exec\n%s", Y, RST);
		}
	}
	else if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
	{
		right = (*node)->data.s_pipe.left->data.s_pipe.right;
		if (right->data.s_exec.fd_out == STDOUT_FILENO)
			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
		else if (right->data.s_exec.fd_out != STDOUT_FILENO)
		{
			dup2(right->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1]);
			if (right->data.s_exec.fd_out > 2)
				close(right->data.s_exec.fd_out);
			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
			//fprintf(stderr, "%sdup2! fd_out - exec\n%s", Y, RST);
		}
	}
	//fprintf(stderr, "%shandle_pipe | CURRENT NODE(after):%s\n", C, RST);
	//print_node((*node));
	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));
	close(s->pipe_fd[cur_pipe][0]);
	close(s->pipe_fd[cur_pipe][1]);
	return (0);
}

//V2.1
//int	handle_pipe(t_shell *s, t_ast **node)
//{
//	int		cur_pipe;
//	t_ast	*right;

//	cur_pipe = s->pipe_count;
//	if (pipe(s->pipe_fd[cur_pipe]) < 0)
//		return (print_error(&s->numerr, errno));
//	//fprintf(stderr, "%shandle_pipe | pipe_in[1]: %d | pipe_out[0]: %d%s\n", Y, s->pipe_fd[s->pipe_count][1], s->pipe_fd[s->pipe_count][0], RST);
//	//fprintf(stderr, "handle_pipe | CURRENT NODE(before):\n");
//	//print_node((*node));
//	if ((*node)->data.s_pipe.right->data.s_exec.fd_in == STDIN_FILENO)
//		(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
//	else if ((*node)->data.s_pipe.right->data.s_exec.fd_in != STDIN_FILENO)
//	{
//		dup2((*node)->data.s_pipe.right->data.s_exec.fd_in, s->pipe_fd[cur_pipe][0]);
//		if ((*node)->data.s_pipe.right->data.s_exec.fd_in > 2)
//			close((*node)->data.s_pipe.right->data.s_exec.fd_in);
//		(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
//		//fprintf(stderr, "%sdup2! fd_in\n%s", Y, RST);
//	}
//	if ((*node)->data.s_pipe.left->tag == EXEC_NODE)
//	{
//		if ((*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
//			(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//		else if ((*node)->data.s_pipe.left->data.s_exec.fd_out != STDOUT_FILENO)
//		{
//			dup2((*node)->data.s_pipe.left->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1]);
//			if ((*node)->data.s_pipe.left->data.s_exec.fd_out > 2)
//				close((*node)->data.s_pipe.left->data.s_exec.fd_out);
//			(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//			//fprintf(stderr, "%sdup2! fd_out - pipe_exec\n%s", Y, RST);
//		}
//	}
//	else if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
//	{
//		right = (*node)->data.s_pipe.left->data.s_pipe.right;
//		if (right->data.s_exec.fd_out == STDOUT_FILENO)
//			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//		else if (right->data.s_exec.fd_out != STDOUT_FILENO)
//		{
//			dup2(right->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1]);
//			if (right->data.s_exec.fd_out > 2)
//				close(right->data.s_exec.fd_out);
//			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//			//fprintf(stderr, "%sdup2! fd_out - exec\n%s", Y, RST);
//		}
//	}
//	//fprintf(stderr, "%shandle_pipe | CURRENT NODE(after):%s\n", C, RST);
//	//print_node((*node));
//	s->pipe_count++;
//	preorder_exec(s, &((*node)->data.s_pipe.left));
//	preorder_exec(s, &((*node)->data.s_pipe.right));
//	close(s->pipe_fd[cur_pipe][0]);
//	close(s->pipe_fd[cur_pipe][1]);
//	return (0);
//}

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
