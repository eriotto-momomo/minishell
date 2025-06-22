/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/22 14:39:26 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_shell *s, t_ast **current_node)
{
	int cur_pipe;
	t_ast *right;

	cur_pipe = s->pipe_count;
	if (pipe(s->pipe_fd[cur_pipe]) < 0)
		return (print_error(&s->numerr, errno, "handle_pipe"));
	if ((*current_node)->data.pipe.left->tag == PIPE_NODE)
	{
		right = (*current_node)->data.pipe.left->data.pipe.right;
		if (right->tag == EXEC_NODE && right->data.exec.fd_out == STDOUT_FILENO)
			right->data.exec.fd_out = s->pipe_fd[cur_pipe][1];
	}
	else if ((*current_node)->data.pipe.left->tag == EXEC_NODE
		&& (*current_node)->data.pipe.left->data.exec.fd_out == STDOUT_FILENO)
		(*current_node)->data.pipe.left->data.exec.fd_out = s->pipe_fd[cur_pipe][1];
    (*current_node)->data.pipe.right->data.exec.fd_in = s->pipe_fd[cur_pipe][0];
	(*current_node)->data.pipe.right->data.exec.fd_in = s->pipe_fd[cur_pipe][0];
	s->pipe_count++;
	preorder_exec(s, &((*current_node)->data.pipe.left));
	preorder_exec(s, &((*current_node)->data.pipe.right));
	close(s->pipe_fd[cur_pipe][0]);
	close(s->pipe_fd[cur_pipe][1]);
	return (0);
}


int	handle_exec(t_shell *s, t_ast *node)
{
	if (ft_strncmp(node->data.exec.argv[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(s, (*node).data.exec.argc, (*node).data.exec.argv));
	if (ft_strncmp(node->data.exec.argv[0], CD, ft_strlen(CD)) == 0)
		return (ft_cd(s, (*node).data.exec.argc, (*node).data.exec.argv));
	if (ft_strncmp(node->data.exec.argv[0], FT_ECHO, ft_strlen(FT_ECHO)) == 0)
		return (ft_echo(s, &node, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], PWD, ft_strlen(PWD)) == 0)
		return (ft_pwd(s, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], ENV, ft_strlen(ENV)) == 0)
		return (ft_env(s, s->env_list, node->data.exec.fd_out));
	if (ft_strncmp(node->data.exec.argv[0], UNSET, ft_strlen(UNSET)) == 0)
		return (ft_unset(s, node->data.exec.argc, node->data.exec.argv));
	if (ft_strncmp(node->data.exec.argv[0], EXPORT, ft_strlen(EXPORT)) == 0)
		return (ft_export(s, &s->env_list, node->data.exec.argc, node->data.exec.argv, node->data.exec.fd_out));
	return (ft_external(s, s->env_list, node));
}

int	setup_pipe(int	fd_in, int fd_out)
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

	cmd_path = pathfinder(env, argv[0]);
	if (!cmd_path)
	{
		s->numerr = 127;
		perror("Command not found");
		terminate_shell(s);
	}
	if (execve(cmd_path, argv, NULL) == -1)
	{
		w_free((void **)&cmd_path);
		s->numerr = 126;
		(perror("Command not executable"));
		terminate_shell(s);
	}
	return (0);
}
