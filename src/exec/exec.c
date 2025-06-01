/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/01 15:34:17 by emonacho         ###   ########.fr       */
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
		//printf("preorder_exec |[AST_PIPE]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
		if (handle_pipe(s, &(*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	else if ((*current_node)->tag == AST_REDIR)
	{
		//printf("preorder_exec |[AST_REDIR]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
		if (handle_redir(s, &(*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	else if ((*current_node)->tag == AST_EXEC)
	{
		//printf("preorder_exec |[AST_EXEC]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
		if (handle_exec(s, (*current_node), fd_in, fd_out) != 0)
			return (1);
	}
	printf("preorder_exec |[EXIT]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	return (0);
}

void	execution(t_shell *s)
{
	int	err;

	s->root_fd = -1;
	s->heredoc_tmp = ft_strdup("./tmp/heredoc_tmp.txt");
	if (!s->heredoc_tmp)
		terminate_shell(s, errno);
	err = preorder_exec(s, &s->current_node, STDIN_FILENO, STDOUT_FILENO);
	s->ret_value = err;
	//if (err != 0)
	//	terminate_shell(s, errno);
	free_ast(&(s->root_node));
	w_free((void **)&s->heredoc_tmp);
	unlink("./tmp/heredoc_tmp.txt");
}
