/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/20 17:29:42 by emonacho         ###   ########.fr       */
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

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (setup_pipe(node->data.exec.fd_in, node->data.exec.fd_out) == -1)
			return (1);
		while (++i < s->pipe_count)
		{
			if (s->pipe_fd[i][0] != node->data.exec.fd_in
				&& s->pipe_fd[i][0] != node->data.exec.fd_out)
				close(s->pipe_fd[i][0]);
			if (s->pipe_fd[i][1] != node->data.exec.fd_in
				&& s->pipe_fd[i][1] != node->data.exec.fd_out)
				close(s->pipe_fd[i][1]);
		}
		cmd_execution(env, node->data.exec.argv);
	}
	else
		s->child_pids[s->pid_count++] = pid;
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **node)
{
	if (!(*node))
		return (0);
	if ((*node)->tag == PIPE_NODE)
	{
		if (handle_pipe(s, &(*node)) != 0)
			return (1);
	}
	else if ((*node)->tag == EXEC_NODE)
	{
		if ((*node)->data.exec.heredoc_count > 0)
			(*node)->data.exec.fd_in = handle_heredoc(s, (*node));
		if (!string_processing(s, &(*node)->data.exec.argc, &(*node)->data.exec.argv))
		{
			perror("Expansion or quote removal failed");
			terminate_shell(s, 0);
		}
		if((*node)->data.exec.argc > 0)
			if (handle_exec(s, (*node)) != 0)
				return (1);
	}
	return (0);
}

void	execution(t_shell *s)
{
	int	i;

	g_status = READY;
	i = 0;
	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		terminate_shell(s, errno);
	setup_signals(s, DEFAULT_SIGNALS);
	preorder_exec(s, &s->current_node);
	while (i < s->pid_count)
	{
		if (g_status == CLEAN_EXIT)
		{
			if (kill(s->child_pids[i], SIGINT) < 0)
				terminate_shell(s, 0);
			g_status = 130;
			break;
		}
		waitpid(s->child_pids[i], NULL, 0);
		i++;
	}
	free_ast(&(s->root_node));
	unlink(HEREDOC_FILE_PATH);
	w_free((void **)&s->heredoc_tmp);
}


