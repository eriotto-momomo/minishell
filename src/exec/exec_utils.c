/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/25 18:29:19 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		printf("fd : %d\n", (*node)->data.s_pipe.right->data.s_exec.fd_in);
    	close(dup_read);
	}
	// (*node)->data.s_pipe.right->data.s_exec.fd_in = dup_read;
	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));
	if (dup_read > 2)
		close(dup_read);
	(*node)->data.s_pipe.right->data.s_exec.fd_in = -1;
	close_pipes((*node), s->pipe_fd, s->pipe_count);
	return (0);
}

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	pid_t	pid;

	(void)env;
	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, NULL, EPIPE));
	if (pid == 0)
	{
		close_pipes(node, s->pipe_fd, s->pipe_count);
		if (node->data.s_exec.fd_in == -1)
			kill_children(s);
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			exit(print_error(&s->numerr, NULL, errno));
		cmd_execution(s, env, node->data.s_exec.av);
		kill_children(s);
	}
	else
	{
		if (f_close(&node->data.s_exec.fd_heredoc) != 0)
			return (1);
		if (f_close(&node->data.s_exec.fd_out) != 0)
			return (1);
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
		print_error(&s->numerr, NULL, ENOMEM);
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
