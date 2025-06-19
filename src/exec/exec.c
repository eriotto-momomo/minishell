/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 17:18:41 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int close_fd(t_ast *node)
{
	if(node->tag == EXEC_NODE)
	{
		if (node->data.exec.fd_in > 2)
			if (close(node->data.exec.fd_in) != 0)
				return (1);
		if (node->data.exec.fd_out > 2)
			if (close(node->data.exec.fd_out) != 0)
				return (1);
	}
	else if(node->tag == PIPE_NODE)
	{
		if (close_fd(node->data.pipe.left) != 0)
			return (1);
		if (close_fd(node->data.pipe.right) != 0)
			return (1);
	}
	node->data.exec.fd_in = 0;
	node->data.exec.fd_out = 1;
	return (0);
}

int	ft_external(t_shell *s, t_env *env, t_ast *current_node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (setup_pipe(current_node->data.exec.fd_in, current_node->data.exec.fd_out) == -1)
			return (1);
		while (++i < s->pipe_count)
		{
			if (s->pipe_fd[i][0] != current_node->data.exec.fd_in
				&& s->pipe_fd[i][0] != current_node->data.exec.fd_out)
				close(s->pipe_fd[i][0]);
			if (s->pipe_fd[i][1] != current_node->data.exec.fd_in
				&& s->pipe_fd[i][1] != current_node->data.exec.fd_out)
				close(s->pipe_fd[i][1]);
		}
		cmd_execution(env, current_node->data.exec.argv);
	}
	else
		s->child_pids[s->pid_count++] = pid;
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **current_node)
{
	if (!(*current_node))
		return (0);
	if ((*current_node)->tag == PIPE_NODE)
	{
		if (handle_pipe(s, &(*current_node)) != 0)
			return (1);
	}
	else if ((*current_node)->tag == EXEC_NODE)
	{
		if ((*current_node)->data.exec.heredoc_count > 0)
			(*current_node)->data.exec.fd_in = handle_heredoc(s, (*current_node));
		if (!string_processing(s, &(*current_node)->data.exec.argc, &(*current_node)->data.exec.argv))
		{
			perror("Expansion or quote removal failed");
			terminate_shell(s, 0);
		}
		if (handle_exec(s, (*current_node)) != 0)
			return (1);
	}
	return (0);
}

void	execution(t_shell *s)
{
	int	i;

	i = 0;
	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		terminate_shell(s, errno);
	setup_signals(s, DEFAULT_SIGNALS);
	preorder_exec(s, &s->current_node);
	while (i < s->pid_count)
	{
		waitpid(s->child_pids[i], NULL, 0);
		if (g_status == CLEAN_EXIT)
		{
			if (kill(s->child_pids[i], SIGINT) < 0)
				terminate_shell(s, 0);
			g_status = 130;
			break;
		}
		i++;
	}
	free_ast(&(s->root_node));
	unlink(HEREDOC_FILE_PATH);
	w_free((void **)&s->heredoc_tmp);
}


