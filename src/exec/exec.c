/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/20 17:27:46 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	preorder_exec(t_shell *s, t_ast **current_node, int fd_in, int fd_out);
static int	handle_exec(t_shell *s, t_ast *current_node, int fd_in, int fd_out);

static int	ft_external(t_env *env, t_ast *current_node, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		handle_pipe(fd_in, fd_out);
		cmd_execution(env, current_node->data.ast_exec.argv);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

static int	handle_redir(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
{
	/*while ((*current_node) && (*current_node)->data.ast_redir.left)	// 📍DESCEND DANS L'AST
	{
		fprintf(stderr, "handle_redir| %s%s%s\n", Y, "Going down the tree...", RST);	// 🖨️PRINT💥DEBUGING
		preorder_exec(s, &(*current_node)->data.ast_redir.left, fd_in, fd_out);
		if (!(*current_node)->data.ast_redir.left)
			break;
	}
	fprintf(stderr, "handle_redir| %s%s%s\n", Y, "Lowest node in the tree reached!", RST);	// 🖨️PRINT💥DEBUGING*/
	if ((*current_node)->data.ast_redir.mode == OUT_REDIR
			|| (*current_node)->data.ast_redir.mode == APP_OUT_REDIR)
	{
		fd_out = redirect(s, (*current_node));
		if (fd_out < 0)
			return (-1);
	}
	else
	{
		fd_in = redirect(s, (*current_node));
		if (fd_in < 0)
			return (-1);
	}
	// BACKUP 💾
	if ((*current_node)->data.ast_redir.left->tag == AST_EXEC)
	{
		fprintf(stderr, "handle_redir| %sWill output/input EXEC_NODE in FD_IN: %d | FD_OUT: %d%s\n", Y, fd_in, fd_out, RST); // 🖨️PRINT💥DEBUGING
		s->current_node = (*current_node)->data.ast_redir.left;	//🚨 NECESSAIRE POUR APPELER LES BUILTINS AVEC LE BON NODE
	}
	if ((*current_node)->data.ast_redir.left)	// 📍DESCEND DANS L'AST
		preorder_exec(s, &(*current_node)->data.ast_redir.left, fd_in, fd_out);
	if ((*current_node)->data.ast_redir.mode == OUT_REDIR
		|| (*current_node)->data.ast_redir.mode == APP_OUT_REDIR)
	{
		if (close(fd_out) < 0)
			return (-1);
	}
	return (0);
}

// BACKUP 💾
/*static int	handle_redir(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
{
	if ((*current_node)->data.ast_redir.mode == OUT_REDIR
			|| (*current_node)->data.ast_redir.mode == APP_OUT_REDIR)
	{
		//fprintf(stderr, "handle_redir| %s%s%s\n", Y, "OUTPUT REDIR DETECTED", RST); // 🖨️PRINT💥DEBUGING
		fd_out = redirect(s);
		if (fd_out < 0)
			return (-1);
	}
	else
	{
		//fprintf(stderr, "handle_redir| %s%s%s\n", Y, "INPUT REDIR DETECTED", RST); // 🖨️PRINT💥DEBUGING
		fd_in = redirect(s);
		if (fd_in < 0)
			return (-1);
	}
	if ((*current_node)->data.ast_redir.left->tag == AST_EXEC)
	{
		fprintf(stderr, "handle_redir| %s%s%s\n", Y, "EXEC DETECTED!", RST); // 🖨️PRINT💥DEBUGING
		handle_exec(s, (*current_node)->data.ast_redir.left, fd_in, fd_out);
	}
	else
		preorder_exec(s, &(*current_node)->data.ast_redir.left, fd_in, fd_out);
	if ((*current_node)->data.ast_redir.mode == OUT_REDIR
		|| (*current_node)->data.ast_redir.mode == APP_OUT_REDIR)
	{
		if (close(fd_out) < 0)
			return (-1);
	}
	return (0);
}*/

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
	return (ft_external(s->env_list, current_node, fd_in, fd_out));
}

static int	preorder_exec(t_shell *s, t_ast **current_node, int fd_in, int fd_out)
{
	int		pipefd[2]; // 🚧 REMPLACER par 's->pipefd'❔ Pour nous permetter ensuite d'appeler une fonction 'handle_pipe'❔ 🚧

	if (!(*current_node))
		return (0);
	fprintf(stderr, "preorder_exec| %s%s%s\n", Y, "↓current_node↓", RST);	// 🖨️PRINT💥DEBUGING
	print_node((*current_node));											// 🖨️PRINT💥DEBUGING
	if ((*current_node)->tag == AST_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(0);
		}
		preorder_exec(s, &((*current_node)->data.ast_pipe.left), fd_in, pipefd[1]);
		close(pipefd[1]);
		preorder_exec(s, &((*current_node)->data.ast_pipe.right), pipefd[0], fd_out);
		close(pipefd[0]);
	}
	else if ((*current_node)->tag == AST_REDIR)
	{
		if (handle_redir(s, &(*current_node), fd_in, fd_out) < 0)
		{
			perror("redir");
			exit(0);
		}
	}
	else if ((*current_node)->tag == AST_EXEC)
	{
		fprintf(stderr, "preorder_exec| output/input exec node in fd[%s%d%s]\n", Y, s->fd, RST); // 🖨️PRINT💥DEBUGING
		// var_expansion(s, (*current_node)->data.ast_exec.argv);
		handle_exec(s, (*current_node), fd_in, fd_out);
		fprintf(stderr, "preorder_exec| %sEXITING handle_exec%s\n", Y, RST); // 🖨️PRINT💥DEBUGING

	}
	return (0);
}

void	execution(t_shell *s)
{
	int	err;

	err = preorder_exec(s, &s->current_node, STDIN_FILENO, STDOUT_FILENO);
	s->ret_value = err;
	free_ast(&(s->root_node));
}
