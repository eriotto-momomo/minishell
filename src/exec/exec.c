/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/13 17:37:41 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int close_fd(t_ast *node)
{
	if(node->tag == EXEC_NODE)
	{
		if (node->data.exec.fd_in > 2)
		{
			if (close(node->data.exec.fd_in) != 0)
				return (1);
		}
		if (node->data.exec.fd_out > 2)
		{
			if (close(node->data.exec.fd_out) != 0)
				return (1);
		}
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

int	ft_external(t_env *env, t_ast *current_node)
{
	//printf("ENTER ft_external | %sfd_in: %d | fd_out: %d%s\n", P, current_node->data.exec.fd_in, current_node->data.exec.fd_out, RST);	// 🖨️PRINT💥DEBUGING
	//print_node(current_node);
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (setup_pipe(current_node->data.exec.fd_in, current_node->data.exec.fd_out) == 1)
			return (1);
		cmd_execution(env, current_node->data.exec.argv);
	}
	waitpid(0, NULL, 0);
	//printf("EXIT ft_external | %sfd_in: %d | fd_out: %d%s\n", P, current_node->data.exec.fd_in, current_node->data.exec.fd_out, RST);	// 🖨️PRINT💥DEBUGING
	return (0);
}

int	preorder_exec(t_shell *s, t_ast **current_node)
{
	//printf("%spreorder_exec | current_node:%s\n", P, RST);									// 🖨️PRINT💥DEBUGING
	//print_node((*current_node));																// 🖨️PRINT💥DEBUGING
	if (!(*current_node))
		return (0);
	if ((*current_node)->tag == PIPE_NODE)
	{
		if (handle_pipe(s, &(*current_node)) != 0)
			return (1);
		//if (close_fd((*current_node)) != 0)
		//	return (1);
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
		if (close_fd((*current_node)) != 0)
			return (1);
	}
	//printf("preorder_exec |[EXIT]%s fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);		// 🖨️PRINT💥DEBUGING
	//print_struct(s);																			// 🖨️PRINT💥DEBUGING
	return (0);
}

void	execution(t_shell *s)
{
	int	err;

	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		terminate_shell(s, errno);
	err = preorder_exec(s, &s->current_node);
	s->ret_value = err;
	//if (err != 0)
	//	terminate_shell(s, errno);
	free_ast(&(s->root_node));
	w_free((void **)&s->heredoc_tmp);
	unlink(HEREDOC_FILE_PATH);
}


