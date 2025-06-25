/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/25 09:28:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	interrupt_heredoc(t_shell *s)
{
	if (access(HEREDOC_FILE_PATH, F_OK) < 0)
	{
		w_free((void **)&s->line);
		print_error(&s->numerr, errno);
		return (1);
	}
	return (0);
}

int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe;
	t_ast	*right;

	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, errno));
	if ((*node)->data.s_pipe.left->tag == PIPE_NODE)
	{
		right = (*node)->data.s_pipe.left->data.s_pipe.right;
		if (right->tag == EXEC_NODE
			&& right->data.s_exec.fd_out == STDOUT_FILENO)
			right->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
	}
	else if ((*node)->data.s_pipe.left->tag == EXEC_NODE
		&& (*node)->data.s_pipe.left->data.s_exec.fd_out == STDOUT_FILENO)
		(*node)->data.s_pipe.left->data.s_exec.fd_out = s->pipe_fd[cur_pipe][1];
	(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
	(*node)->data.s_pipe.right->data.s_exec.fd_in = s->pipe_fd[cur_pipe][0];
	s->pipe_count++;
	preorder_exec(s, &((*node)->data.s_pipe.left));
	preorder_exec(s, &((*node)->data.s_pipe.right));
	close(s->pipe_fd[cur_pipe][0]);
	close(s->pipe_fd[cur_pipe][1]);
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

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			return (print_error(&s->numerr, errno));
		while (++i < s->pipe_count)
		{
			if (s->pipe_fd[i][0] != node->data.s_exec.fd_in
				&& s->pipe_fd[i][0] != node->data.s_exec.fd_out)
				close(s->pipe_fd[i][0]);
			if (s->pipe_fd[i][1] != node->data.s_exec.fd_in
				&& s->pipe_fd[i][1] != node->data.s_exec.fd_out)
				close(s->pipe_fd[i][1]);
		}
		cmd_execution(s, env, node->data.s_exec.av);
	}
	else
		s->child_pids[s->pid_count++] = pid;
	return (0);
}

int	is_path(const char *cmd)
{
	if (!cmd)
		return (0);
	return (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/'
		|| (cmd[1] == '.' && cmd[2] == '/'))));
}

char	*path_making(t_env *env, char *cmd)
{
	char *cmd_path;

	if (is_path(cmd))
	{
		cmd_path = ft_strdup(cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == -1)
		{
			w_free((void **)&cmd_path);
			return (NULL);
		}
	}
	else
	{
		cmd_path = pathfinder(env, cmd);
		if (!cmd_path)
			return (NULL);
	}
	return (cmd_path);
}

int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	**env_table;
	char	*path;
	
	path = path_making(env, argv[0]);
	if (!path)
	{
		w_free((void **)&path);
		print_custom_error(&s->numerr, 127, "Command not found\n");
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
