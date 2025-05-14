/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/14 08:51:43 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_execution(char **argv)
{
	char	*cmd_path;
	
	cmd_path = pathfinder(argv[0]);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(127);
	}
	if (execve(cmd_path, argv, NULL) == -1)
	{
		w_free((void **)&cmd_path);
		perror("Command not executable");
		exit(126);
	}
}

static int	ft_external(t_ast *current_node, int fd_in, int fd_out)
{
	pid_t pid;
	
	pid = fork();
		if (pid == 0)
		{
			handle_pipe(fd_in, fd_out);
			cmd_execution(current_node->data.ast_exec.argv);
		}
		else if (pid > 0)
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
	else if ((*current_node)->tag == AST_EXEC)
		handle_exec(s, (*current_node), fd_in, fd_out);
	return (0);
}
