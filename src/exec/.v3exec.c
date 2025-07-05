/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/07/05 11:52:27 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_fd(t_ast *node)
{
	//if (errno == 9)
	//{
	//	errno = 0;
	//	return (0);
	//}
	if (node->tag == EXEC_NODE)
	{
		fprintf(stderr, "close_fd | current node:\n");
		print_node(node);
		if (node->data.s_exec.fd_in > 2)
		{
			fprintf(stderr, "close_fd | closing fd_in: %d\n", node->data.s_exec.fd_in);
			if (close(node->data.s_exec.fd_in) != 0)
			{
				fprintf(stderr, "close_fd | %sissue while closing fd_in: %d%s\n", R, node->data.s_exec.fd_in, RST);
				//return (1);
			}
		}
		if (node->data.s_exec.fd_out > 2)
		{
			fprintf(stderr, "close_fd | closing fd_out: %d\n", node->data.s_exec.fd_out);
			if (close(node->data.s_exec.fd_out) != 0)
			{
				fprintf(stderr, "close_fd | %sissue while closing fd_out: %d%s\n", R, node->data.s_exec.fd_out, RST);
				//return (1);
			}
		}
		node->data.s_exec.fd_in = 0;
		node->data.s_exec.fd_out = 1;
		return (0);
	}
	else if (node->tag == PIPE_NODE)
	{
		if (close_fd(node->data.s_pipe.left) != 0)
			return (1);
		if (close_fd(node->data.s_pipe.right) != 0)
			return (1);
	}
	return (0);
}

int	handle_exec(t_shell *s, t_ast *node)
{
	if (perfect_match(node->data.s_exec.av[0], "exit"))
		return (ft_exit(s, (*node).data.s_exec.ac, (*node).data.s_exec.av));
	if (perfect_match(node->data.s_exec.av[0], CD))
		return (ft_cd(s, (*node).data.s_exec.ac, (*node).data.s_exec.av));
	if (perfect_match(node->data.s_exec.av[0], FT_ECHO))
		return (ft_echo(s, &node, node->data.s_exec.fd_out));
	if (perfect_match(node->data.s_exec.av[0], PWD))
		return (ft_pwd(s, node->data.s_exec.fd_out));
	if (perfect_match(node->data.s_exec.av[0], ENV))
		return (ft_env(s, s->env_list, node->data.s_exec.fd_out));
	if (perfect_match(node->data.s_exec.av[0], UNSET))
		return (ft_unset(s, node->data.s_exec.ac, node->data.s_exec.av));
	if (perfect_match(node->data.s_exec.av[0], EXPORT))
		return (ft_export(s, &s->env_list, node));
	else
	{
		g_sig = 0;
		s->child_exit = 1;
		return (ft_external(s, s->env_list, node));
	}
}

static int	process_exec_node(t_shell *s, t_ast **n)
{
	if ((*n)->data.s_exec.fd_in < 0)
		return (print_error(&s->numerr, errno));
	if (string_processing(s, &(*n)->data.s_exec.ac,
			&(*n)->data.s_exec.av) != 0)
		return (1);
	if ((*n)->data.s_exec.inredir_priority == HERE_DOC)
	{
		//fprintf(stderr, "%sprocess_exec_node | (*n)->data.s_exec.path_tmp_file: [%s]%s\n", G, (*n)->data.s_exec.path_tmp_file, RST);
		//if (access((*n)->data.s_exec.path_tmp_file, F_OK) != 0) //DEBUG
		//	perror("access F_OK"); //DEBUG
		//fprintf(stderr, "process_exec_node | PATH TEST: [%s]\n", "./TEST_PATH");
		//if (access("./TEST_PATH", F_OK) != 0) //DEBUG
		//	perror("access F_OK"); //DEBUG
		//(*n)->data.s_exec.fd_in
		//	= open((*n)->data.s_exec.path_tmp_file, O_RDONLY);
		//fprintf(stderr, "%sprocess_exec_node | (*n)->data.s_exec.fd_in: %d%s\n", G, (*n)->data.s_exec.fd_in, RST);
		//(*n)->data.s_exec.fd_heredoc
		//	= open((*n)->data.s_exec.path_tmp_file, O_RDONLY);
		//fprintf(stderr, "%sprocess_exec_node | (*n)->data.s_exec.fd_heredoc: %d%s\n", G, (*n)->data.s_exec.fd_heredoc, RST);

		//if ((*n)->data.s_exec.fd_in != STDIN_FILENO)
		//	close((*n)->data.s_exec.fd_in);
		//(*n)->data.s_exec.fd_in = (*n)->data.s_exec.fd_heredoc;
		//if ((*n)->data.s_exec.fd_in < 0)
		//	return (1);
		fprintf(stderr, "%sprocess_exec_node | (*n)->data.s_exec.path_tmp_file: [%s]%s\n", G, (*n)->data.s_exec.path_tmp_file, RST);
		(*n)->data.s_exec.fd_in
			= open((*n)->data.s_exec.path_tmp_file, O_RDONLY);
		if ((*n)->data.s_exec.fd_in < 0)
			return (1);
		fprintf(stderr, "%sprocess_exec_node | (*n)->data.s_exec.fd_in: %d%s\n", G, (*n)->data.s_exec.fd_in, RST);

	}
	if ((*n)->data.s_exec.ac > 0)
		if (handle_exec(s, (*n)) != 0)
			return (1);
	//if ((*n)->data.s_exec.fd_heredoc > 2)
	//	if (close((*n)->data.s_exec.fd_heredoc) != 0)
	//		return (1);
	//if ((*n)->data.s_exec.fd_out > 2)
	//	if (close((*n)->data.s_exec.fd_out) != 0)
	//		return (1);
	//if ((*n)->data.s_exec.fd_in > 2)
	//	if (close((*n)->data.s_exec.fd_in) != 0)
			return (1);
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **node)
{
	//fprintf(stderr, "preorder_exec | CURRENT NODE:\n");
	//print_node((*node));
	if (!(*node))
		return (0);
	if ((*node)->tag == PIPE_NODE)
	{
		if (handle_pipe(s, &(*node)) != 0)
			return (1);
	}
	else if ((*node)->tag == EXEC_NODE)
		process_exec_node(s, node);
	//close_fd((*node));
	return (0);
}

static int	waiton(uint8_t *numerr, int *child_pids, int pid_count)
{
	int	i;
	int	status;
	int	pid;

	i = 0;
	while (i < pid_count)
	{
		pid = waitpid(child_pids[i], &status, 0);
		if (pid == -1)
			continue ;
		if (WIFEXITED(status))
			*numerr = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*numerr = WTERMSIG(status);
		i++;
	}
	return (0);
}

int	execution(t_shell *s)
{
	int	i;

	i = 0;
	setup_signals(s, DEFAULT_SIGNALS);
	if (preorder_exec(s, &s->current_node) != 0)
		return (1);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
	{
		while (i < s->pid_count)
		{
			if (kill(s->child_pids[i], SIGKILL) != 0)
				return (print_error(&s->numerr, errno));
			i++;
		}
	}
	waiton(&s->numerr, s->child_pids, s->pid_count);
	close_fd(s->root_node); // NORMALEMENT USELESS
	if (s->tmp_files_list != NULL)
		w_free((void **)&(s->tmp_files_list)); // BIZARRE: possible de faire dans `reset`?
	return (0);
}
