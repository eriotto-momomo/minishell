/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/22 17:51:34 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_external(t_env *env, t_ast *current_node, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (setup_pipe(fd_in, fd_out) == 1)
			return (1);
		cmd_execution(env, current_node->data.ast_exec.argv);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
{
	if (!(*current_node))
		return (0);
	if ((*current_node)->tag == AST_PIPE)
	{
		if (handle_pipe(s, &(*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	else if ((*current_node)->tag == AST_REDIR)
	{
		if (handle_redir(s, &(*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	else if ((*current_node)->tag == AST_EXEC)
	{
		if (handle_exec(s, (*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	return (0);
}

void	execution(t_shell *s)
{
	int	err;

	s->root_fd = -1;
	err = preorder_exec(s, &s->current_node, STDIN_FILENO, STDOUT_FILENO);
	s->ret_value = err;
	//if (err != 0)
	//	terminate_shell(s, errno);
	free_ast(&(s->root_node));
}
