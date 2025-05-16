/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 13:12:15 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_external(t_ast *current_node, int fd_in, int fd_out)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		handle_pipe(fd_in, fd_out);
		cmd_execution(current_node->data.ast_exec.argv);
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

static int	handle_exec(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	if (ft_strncmp(current_node->data.ast_exec.argv[0], CD, ft_strlen(CD)) == 0)
		return (ft_cd(s));
	if (ft_strncmp(current_node->data.ast_exec.argv[0], ECHO, ft_strlen(ECHO)) == 0)
		return (ft_echo(s, fd_out));
	if (ft_strncmp(current_node->data.ast_exec.argv[0], PWD, ft_strlen(PWD)) == 0)
		return (ft_pwd(s, fd_out));
	if (ft_strncmp(current_node->data.ast_exec.argv[0], ENV, ft_strlen(ENV)) == 0)
		return (ft_env(s, fd_out));
	if (ft_strncmp(current_node->data.ast_exec.argv[0], UNSET, ft_strlen(UNSET)) == 0)
		return (ft_unset(s));
	if (ft_strncmp(current_node->data.ast_exec.argv[0], EXPORT, ft_strlen(EXPORT)) == 0)
		return (ft_export(s));
	return (ft_external(current_node, fd_in, fd_out));
}

int	execution(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
{
	int		pipefd[2];

	if ((*current_node)->tag == AST_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(0);
		}
		execution(s, &((*current_node)->data.ast_pipe.left), fd_in, pipefd[1]);
		close(pipefd[1]);
		execution(s, &((*current_node)->data.ast_pipe.right), pipefd[0], fd_out);
		close(pipefd[0]);
	}
	/*else if ((*current_node)->tag == AST_REDIR)
	{
		if ((*current_node)->data.ast_redir.mode == OUT_REDIR
			|| (*current_node)->data.ast_redir.mode == APP_OUT_REDIR)
			execution(s, &((*current_node)->data.ast_redir.left), fd_in, redirect(s));
		else
			execution(s, &((*current_node)->data.ast_redir.left), redirect(s), fd_out);
	}*/
	else if ((*current_node)->tag == AST_EXEC)
		handle_exec(s, (*current_node), fd_in, fd_out);
	return (0);
}

