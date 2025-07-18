/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/07/18 14:59:49 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	pid_t	pid;


	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, NULL, EPIPE));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			exit(print_error(&s->numerr, NULL, errno));
		close_pipes(s->pipe_count, s->pipe_fd);
		close_fds(s->root_node);
		cmd_execution(s, env, node->data.s_exec.av);
		kill_children(s); //🚨 Ca marche aussi ici plutot que dans `cmd_execution`?
	}
	else
	{
		s->child_pids[s->pid_count++] = pid;
		//if (node->data.s_exec.fd_in != STDIN_FILENO && is_open(node->data.s_exec.fd_in))
		//	close(node->data.s_exec.fd_in); //🚨
		//if (node->data.s_exec.fd_out != STDOUT_FILENO && is_open(node->data.s_exec.fd_out))
		//	close(node->data.s_exec.fd_out); //🚨
	}
	return (0);
}

static int	handle_exec(t_shell *s, t_ast *node)
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
		return (print_error(&s->numerr, NULL, errno));
	if (string_processing(s, &(*n)->data.s_exec.ac,
			&(*n)->data.s_exec.av) != 0)
		return (1);
	if ((*n)->data.s_exec.inredir_priority == HERE_DOC)
	{
		if ((*n)->data.s_exec.fd_in > 2 && is_open((*n)->data.s_exec.fd_in))
			close((*n)->data.s_exec.fd_in);
		(*n)->data.s_exec.fd_in
			= open((*n)->data.s_exec.path_tmp_file, O_RDONLY);
		if ((*n)->data.s_exec.fd_in < 0)
			return (1);
	}
	if ((*n)->data.s_exec.ac > 0)
		if (handle_exec(s, (*n)) != 0)
			return (1);
	//if ((*n)->data.s_exec.fd_out > 2&& is_open((*n)->data.s_exec.fd_out))
	//	if (close((*n)->data.s_exec.fd_out) != 0)
	//		return (1);
	//if ((*n)->data.s_exec.fd_in > 2 && is_open((*n)->data.s_exec.fd_in))
	//	if (close((*n)->data.s_exec.fd_in) != 0)
			return (1);
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
		if ((*node)->data.s_exec.fd_in < 0 || (*node)->data.s_exec.fd_out < 0)
		{
			//fprintf(stderr, "%spreorder_exec | invalid fds for exec | return (0);%s\n", R, RST);
			return (0);
		}
		process_exec_node(s, node);
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
				return (print_error(&s->numerr, NULL, errno));
			i++;
		}
	}
	waiton(&s->numerr, s->child_pids, s->pid_count);
	close_fds(s->root_node);					//🚨 USELESS ?
	close_pipes(s->pipe_count, s->pipe_fd);		//🚨 USELESS ?
	if (s->tmp_files_list != NULL)
		unlink_tmp_files(s->tmp_files_list, s->heredoc_count);
	if (s->tmp_files_list != NULL)
		w_free((void **)&(s->tmp_files_list));	//🚨 BIZARRE: possible de faire dans `reset`?
	return (0);
}
