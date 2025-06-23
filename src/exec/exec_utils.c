/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/23 11:44:00 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_shell *s, t_ast **node)
{
	int		cur_pipe;
	t_ast	*right;

	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, errno, "handle_pipe"));
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

int	handle_exec(t_shell *s, t_ast *node)
{
	if (ft_strncmp(node->data.s_exec.av[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(s, (*node).data.s_exec.ac, (*node).data.s_exec.av));
	if (ft_strncmp(node->data.s_exec.av[0], CD, ft_strlen(CD)) == 0)
		return (ft_cd(s, (*node).data.s_exec.ac, (*node).data.s_exec.av));
	if (ft_strncmp(node->data.s_exec.av[0], FT_ECHO, ft_strlen(FT_ECHO)) == 0)
		return (ft_echo(s, &node, node->data.s_exec.fd_out));
	if (ft_strncmp(node->data.s_exec.av[0], PWD, ft_strlen(PWD)) == 0)
		return (ft_pwd(s, node->data.s_exec.fd_out));
	if (ft_strncmp(node->data.s_exec.av[0], ENV, ft_strlen(ENV)) == 0)
		return (ft_env(s, s->env_list, node->data.s_exec.fd_out));
	if (ft_strncmp(node->data.s_exec.av[0], UNSET, ft_strlen(UNSET)) == 0)
		return (ft_unset(s, node->data.s_exec.ac, node->data.s_exec.av));
	if (ft_strncmp(node->data.s_exec.av[0], EXPORT, ft_strlen(EXPORT)) == 0)
		return (ft_export(s, &s->env_list, node));
	return (ft_external(s, s->env_list, node));
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

int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	*cmd_path;
	char	**env_table;

	cmd_path = pathfinder(env, argv[0]);
	if (!cmd_path)
	{
		print_custom_error(&s->numerr, 127,  "Comand not found: No such file or directory\n");
		terminate_shell(s);
	}
	env_table = ltotable(env);
	if (!env_table)
	{
		w_free((void **)&cmd_path);
		print_error(&s->numerr, ENOMEM, "cmd_execution");
		terminate_shell(s);
	}
	if (execve(cmd_path, argv, env_table) == -1)
	{
		w_free((void **)&cmd_path);
		ft_free_char_array(env_table, count_var(env));
		print_custom_error(&s->numerr, 126, strerror(errno));
		terminate_shell(s);
	}
	return (0);
}
