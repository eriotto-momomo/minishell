/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/03 09:09:25 by timmi            ###   ########.fr       */
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


int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe = s->pipe_count;
	t_ast	*right;
	int		dup_read;

	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, errno));

	// Attribution des fd_out
	if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
	{
		right = (*node)->data.s_pipe.left->data.s_pipe.right;
		if (right->tag == EXEC_NODE && right->data.s_exec.fd_out == STDOUT_FILENO)
			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
	}
	else if ((*node)->data.s_pipe.left->tag == EXEC_NODE
		&& (*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
		(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];

	// Attribution des fd_in
	dup_read = dup(s->pipe_fd[cur_pipe][0]);
	if (dup_read < 0)
		return (print_error(&s->numerr, errno));
	(*node)->data.s_pipe.right->data.s_exec.fd_in = dup_read;

	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));

	// Fermeture dans le parent
	if (dup_read > 2)
		close(dup_read);
	(*node)->data.s_pipe.right->data.s_exec.fd_in = -1;

	if (s->pipe_fd[cur_pipe][0] != -1)
		close(s->pipe_fd[cur_pipe][0]);
	if (s->pipe_fd[cur_pipe][1] != -1)
		close(s->pipe_fd[cur_pipe][1]);
	s->pipe_fd[cur_pipe][0] = -1;
	s->pipe_fd[cur_pipe][1] = -1;

	return (0);
}


int	setup_pipe(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
    	dup2(fd_in, STDIN_FILENO);
    	close(fd_in);
	}

	if (fd_out != STDOUT_FILENO)
	{
    	dup2(fd_out, STDOUT_FILENO);
    	close(fd_out);
	}
	return (0);
}

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (pid == 0)
	{
		close_pipes(node, s->pipe_fd, s->pipe_count);
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			exit(print_error(&s->numerr, errno));
		cmd_execution(s, env, node->data.s_exec.av);
	}
	else
	{
		if (node->data.s_exec.fd_heredoc > 2)
		{
			close(node->data.s_exec.fd_heredoc);
			node->data.s_exec.fd_heredoc = -1;
		}
		if (node->data.s_exec.fd_out > 2)
		{
			close(node->data.s_exec.fd_out);
			node->data.s_exec.fd_out = -1;
		}
		s->child_pids[s->pid_count++] = pid;
	}
	return (0);
}


int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	**env_table;
	char	*path;

	path = path_making(env, argv[0]);
	if (!path)
	{
		w_free((void **)&path);
		print_custom_error(&s->numerr, 127, "Command not found");
		kill_children(s);
	}
	env_table = ltotable(env);
	if (!env_table)
	{
		w_free((void **)&path);
		print_error(&s->numerr, ENOMEM);
		kill_children(s);
	}
	if (execve(path, argv, env_table) == -1)
	{
		w_free((void **)&path);
		ft_free_char_array(env_table, count_var(env));
		print_custom_error(&s->numerr, 126, strerror(errno));
		kill_children(s);
	}
	return (0);
}