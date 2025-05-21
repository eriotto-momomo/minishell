/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/21 16:22:47 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_external(t_env *env, t_ast *current_node, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!setup_pipe(fd_in, fd_out))
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
		if (!handle_pipe(s, &(*current_node), fd_in, fd_out))
		{
			errno = EBADF;
			perror("pipe");
			exit(0);
		}
	}
	else if ((*current_node)->tag == AST_REDIR)
	{
		if (!handle_redir(s, &(*current_node), fd_in, fd_out))
		{
			perror("redir");
			exit(0);
		}
	}
	else if ((*current_node)->tag == AST_EXEC)
	{
		var_expansion(s, (*current_node)->data.ast_exec.argv);
		handle_exec(s, (*current_node), fd_in, fd_out);
	}
	return (0);
}

// BACKUP 💾
//static int	preorder_exec(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
//{
//	int		pipefd[2]; // 🚧 REMPLACER par 's->pipefd'❔ Pour nous permetter ensuite d'appeler une fonction 'handle_pipe'❔ 🚧

//	if (!(*current_node))
//		return (0);
//	//fprintf(stderr, "preorder_exec| %s%s%s\n", Y, "↓current_node↓", RST);	// 🖨️PRINT💥DEBUGING
//	//print_node((*current_node));											// 🖨️PRINT💥DEBUGING
//	if ((*current_node)->tag == AST_PIPE)
//	{
//		if (pipe(pipefd) == -1)
//		{
//			perror("pipe");
//			exit(0);
//		}
//		preorder_exec(s, &((*current_node)->data.ast_pipe.left), fd_in, pipefd[1]);
//		close(pipefd[1]);
//		preorder_exec(s, &((*current_node)->data.ast_pipe.right), pipefd[0], fd_out);
//		close(pipefd[0]);
//	}
//	else if ((*current_node)->tag == AST_REDIR)
//	{
//		if (!handle_redir(s, &(*current_node), fd_in, fd_out))
//		{
//			perror("redir");
//			exit(0);
//		}
//	}
//	else if ((*current_node)->tag == AST_EXEC)
//	{
//		//fprintf(stderr, "preorder_exec| output/input exec node in fd[%s%d%s]\n", Y, s->fd, RST); // 🖨️PRINT💥DEBUGING
//		var_expansion(s, (*current_node)->data.ast_exec.argv);
//		handle_exec(s, (*current_node), fd_in, fd_out);
//	}
//	return (0);
//}

void	execution(t_shell *s)
{
	int	err;

	err = preorder_exec(s, &s->current_node, STDIN_FILENO, STDOUT_FILENO);
	s->ret_value = err;
	free_ast(&(s->root_node));
}
