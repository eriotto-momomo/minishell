/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:08:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/25 13:50:18 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(int count, int pipe_fd[][2])
{
	int	i;
	int	tmp;

	tmp = errno;
	i = -1;
	while (++i < count)
	{
		//fprintf(stderr, "%sclose_pipes | pipe_fd[%d][0]: %d | pipe_fd[%d][1]: %d%s\n", C, i, pipe_fd[i][0], i, pipe_fd[i][1], RST);
		if (is_open(pipe_fd[i][0]))
			close(pipe_fd[i][0]);
		if (is_open(pipe_fd[i][1]))
			close(pipe_fd[i][1]);
	}
	if (errno != tmp)
		errno = tmp;
}

// V3
static void	add_to_pipeline(int *node_fd, int pipe_fd, int mode)
{
	int	fd;

	//fprintf(stderr, "%sadd_to_pipeline | node_fd: %d | pipe_fd: %d | mode: %d%s\n", Y, *node_fd, pipe_fd, mode, RST);
	if (mode == IN_REDIR)
		fd = STDIN_FILENO;
	else if (mode == OUT_REDIR)
		fd = STDOUT_FILENO;
	if (*node_fd == fd)
		*node_fd = pipe_fd;
	else if(*node_fd != fd)
	{
		if (mode == OUT_REDIR)
		{
			// 🚧 dup et close pas necessaires?
			//fprintf(stderr, "%sadd_to_pipeline | OUT_REDIR%s\n", Y, RST);
			if (dup2(*node_fd, pipe_fd) == -1)
			{
				fprintf(stderr, "%sadd_to_pipeline | dup2 failed!%s\n", R, RST);
				perror("dup2 failed"); //🚨DEBUG
			}
			if (*node_fd > 2 && is_open(*node_fd))
				close(*node_fd); //🚨
			*node_fd = pipe_fd;
		}
		else if (mode == IN_REDIR)
		{
			//return ;
			fprintf(stderr, "%sadd_to_pipeline | IN_REDIR%s\n", Y, RST);
			 //🚧 dup et close pas necessaires?
			if (dup2(pipe_fd, *node_fd) == -1)
			{
				fprintf(stderr, "%sadd_to_pipeline | dup2 failed!%s\n", R, RST);
				perror("dup2 failed"); //🚨DEBUG
			}
			if (pipe_fd > 2 && is_open(pipe_fd))
				close(pipe_fd);
			pipe_fd = *node_fd;
		}
	}
}

// BACKUP V2
//static void	add_to_pipeline(int *node_fd, int pipe_fd, int mode)
//{
//	int	fd;

//	if (mode == IN_REDIR)
//		fd = STDIN_FILENO;
//	else if (mode == OUT_REDIR)
//		fd = STDOUT_FILENO;
//	if (*node_fd == fd)
//		*node_fd = pipe_fd;
//	else if(*node_fd != fd)
//	{
//		if (mode == OUT_REDIR)
//		{
//			fprintf(stderr, "add_to_pipeline | OUT_REDIR\n");
//			if (dup2(*node_fd, pipe_fd) == -1)
//			{
//				fprintf(stderr, "%sadd_to_pipeline | dup2 failed!%s\n", R, RST);
//				perror("dup2 failed"); //🚨DEBUG
//			}
//			if (*node_fd > 2 && is_open(*node_fd))
//				close(*node_fd);
//			*node_fd = pipe_fd;
//		}
//		else if (mode == IN_REDIR)
//		{
//			fprintf(stderr, "add_to_pipeline | IN_REDIR\n");
//			if (dup2(pipe_fd, *node_fd) == -1)
//			{
//				fprintf(stderr, "%sadd_to_pipeline | dup2 failed!%s\n", R, RST);
//				perror("dup2 failed"); //🚨DEBUG
//			}
//			if (pipe_fd > 2 && is_open(pipe_fd))
//				close(pipe_fd);
//			pipe_fd = *node_fd;
//		}
//	}
//}

// BACKUP V1
//static void	add_to_pipeline(int *node_fd, int pipe_fd, int mode)
//{
//	int	fd;

//	if (mode == IN_REDIR)
//		fd = STDIN_FILENO;
//	else if (mode == OUT_REDIR)
//		fd = STDOUT_FILENO;
//	if (*node_fd == fd)
//		*node_fd = pipe_fd;
//	else if(*node_fd != fd)
//	{
//		if (dup2(*node_fd, pipe_fd) == -1)
//		{
//			fprintf(stderr, "%sadd_to_pipeline | dup2 failed!%s\n", R, RST);
//			perror("dup2 failed"); //🚨DEBUG
//		}
//		if (*node_fd > 2 && is_open(*node_fd))
//			close(*node_fd);
//		*node_fd = pipe_fd;
//	}
//}

//static int	is_valid_fd(t_ast **node)
//{
//	t_ast	*right;
//	int		ret;

//	ret = 0;
//	if ((*node)->data.s_pipe.right->tag == EXEC_NODE)
//	{
//		ret = is_open((*node)->data.s_pipe.right->data.s_exec.fd_in);
//		ret = is_open((*node)->data.s_pipe.right->data.s_exec.fd_out);
//	}
//	if ((*node)->data.s_pipe.left->tag == EXEC_NODE)
//	{
//		ret = is_open((*node)->data.s_pipe.left->data.s_exec.fd_in);
//		ret = is_open((*node)->data.s_pipe.left->data.s_exec.fd_out);
//	}
//	else if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
//	{
//		right = (*node)->data.s_pipe.left->data.s_pipe.right;
//		ret = is_open(right->data.s_exec.fd_in);
//		ret = is_open(right->data.s_exec.fd_out);
//	}
//	if (ret != 0)
//		return (1);
//	return (0);
//}

// V3
int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe;
	t_ast	*right;

	fprintf(stderr, "%shandle_pipe| current_node BEFORE DUPS:%s\n", B, RST);
	print_node((*node));
	//if (is_valid_fd(&(*node)) != 0)
	//{
	//	fprintf(stderr, "%shandle_pipe | is_valid_fd != 0%s\n", R, RST);
	//	return (0);
	//}
	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, NULL, errno));
	fprintf(stderr, "%shandle_pipe | s->pipe_fd[cur_pipe][0]: %d | s->pipe_fd[cur_pipe][1]: %d%s\n", G, s->pipe_fd[cur_pipe][0], s->pipe_fd[cur_pipe][1], RST);
	if ((*node)->data.s_pipe.right->tag == EXEC_NODE)
		add_to_pipeline(&(*node)->data.s_pipe.right->data.s_exec.fd_in, s->pipe_fd[cur_pipe][0], IN_REDIR);
	if ((*node)->data.s_pipe.left->tag == EXEC_NODE)
		add_to_pipeline(&(*node)->data.s_pipe.left->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1], OUT_REDIR);
	else if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
	{
		right = (*node)->data.s_pipe.left->data.s_pipe.right;
		add_to_pipeline(&right->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1], OUT_REDIR);
	}
	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));
	fprintf(stderr, "%shandle_pipe| current_node AFTER DUPS:%s\n", B, RST);
	print_node((*node));
	close(s->pipe_fd[cur_pipe][0]);
	close(s->pipe_fd[cur_pipe][1]);
	return (0);
} //🚨

// BACKUP V2
//int	handle_pipe(t_shell *s, t_ast **node)
//{
//	int		cur_pipe;
//	t_ast	*right;

//	cur_pipe = s->pipe_count;
//	fprintf(stderr, "%shandle_pipe| current_node BEFORE DUPS:%s\n", B, RST);
//	print_node((*node));
//	if (pipe(s->pipe_fd[cur_pipe]) < 0)
//		return (print_error(&s->numerr, errno));
//	fprintf(stderr, "%shandle_pipe | s->pipe_fd[cur_pipe][0]: %d | s->pipe_fd[cur_pipe][1]: %d%s\n", G, s->pipe_fd[cur_pipe][0], s->pipe_fd[cur_pipe][1], RST);
//	add_to_pipeline(&(*node)->data.s_pipe.right->data.s_exec.fd_in, s->pipe_fd[cur_pipe][0], IN_REDIR);
//	if ((*node)->data.s_pipe.left->tag == EXEC_NODE)
//		add_to_pipeline(&(*node)->data.s_pipe.left->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1], OUT_REDIR);
//	else if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
//	{
//		right = (*node)->data.s_pipe.left->data.s_pipe.right;
//		add_to_pipeline(&right->data.s_exec.fd_out, s->pipe_fd[cur_pipe][1], OUT_REDIR);
//	}
//	s->pipe_count++;
//	preorder_exec(s, &((*node)->data.s_pipe.left));
//	preorder_exec(s, &((*node)->data.s_pipe.right));
//	fprintf(stderr, "%shandle_pipe| current_node AFTER DUPS:%s\n", B, RST);
//	print_node((*node));
//	close(s->pipe_fd[cur_pipe][0]);
//	close(s->pipe_fd[cur_pipe][1]);
//	return (0);
//} //🚨

// BACKUP V1
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

// V1
//static void	process_pipe_node(t_shell *s, t_ast **node, int cur_pipe)
//{
//	t_ast	*right;

//	right = (*node)->data.s_pipe.left->data.s_pipe.right;
//	if (right->tag == EXEC_NODE
//		&& right->data.s_exec.fd_out == STDOUT_FILENO)
//		right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//}

//// V1
//int	handle_pipe(t_shell *s, t_ast **node)
//{
//	int		cur_pipe;
//	int		dup_read;

//	cur_pipe = s->pipe_count;
//	if (pipe(s->pipe_fd[cur_pipe]) < 0)
//		return (print_error(&s->numerr, errno));
//	if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
//		process_pipe_node(s, node, cur_pipe);
//	else if ((*node)->data.s_pipe.left->tag == EXEC_NODE
//		&& (*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
//		(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
//	dup_read = dup(s->pipe_fd[cur_pipe][0]);
//	if (dup_read < 0)
//		return (print_error(&s->numerr, errno));
//	(*node)->data.s_pipe.right->data.s_exec.fd_in = dup_read;
//	s->pipe_count++;
//	preorder_exec(s, &((*node)->data.s_pipe.left));
//	preorder_exec(s, &((*node)->data.s_pipe.right));
//	if (dup_read > 2)
//		close(dup_read);
//	(*node)->data.s_pipe.right->data.s_exec.fd_in = -1;
//	close_pipes(s->pipe_count, s->pipe_fd);
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
