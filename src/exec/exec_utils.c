/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/04 16:10:46 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_node(t_ast *ast) // 🖨️PRINT💥DEBUGING
{
	t_ast	*left;
	t_ast	*right;
	int i = 0;

	fprintf(stderr, "%s======== 🖨️PRINT 💥DEBUGING ========%s\n", G, RST);
	if (ast->tag == EXEC_NODE)
	{
		fprintf(stderr, "%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		fprintf(stderr, "%sprint_node%s| argc: %d\n", B, RST, ast->data.s_exec.ac);
		fprintf(stderr, "%sprint_node%s| args:", B, RST);
		i = 0;
		while (i < ast->data.s_exec.ac)
		{
			fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.av[i], RST);
			i++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%sprint_node%s| fd_in:  %s%d%s\n", B, RST, C, ast->data.s_exec.fd_in, RST);
		fprintf(stderr, "%sprint_node%s| fd_out: %s%d%s\n", B, RST, C, ast->data.s_exec.fd_out, RST);
		if (ast->data.s_exec.fd_heredoc > 2)
			fprintf(stderr, "%sprint_node%s| fd_heredoc: %s%d%s\n", B, RST, C, ast->data.s_exec.fd_heredoc, RST);
		fprintf(stderr, "%sprint_node%s| inredir_priority: %d\n", B, RST, ast->data.s_exec.inredir_priority);
		if (ast->data.s_exec.path_tmp_file != NULL)
			fprintf(stderr, "%sprint_node%s| path_tmp_file:  %s%s%s\n", B, RST, C, ast->data.s_exec.path_tmp_file, RST);
		if (ast->data.s_exec.eof_count == 0)
			fprintf(stderr, "%sprint_node%s| No heredoc to handle\n", B, RST);
		else if (ast->data.s_exec.eof_count > 0)
		{
			fprintf(stderr, "%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.s_exec.eof_count)
			{
				fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.eof_list[i], RST);
				i++;
			}
			fprintf(stderr, "\n");
		}
	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.s_pipe.left;
		right = ast->data.s_pipe.right;
		fprintf(stderr, "%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		if (left->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| L. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		fprintf(stderr, "%s------------------------------------%s\n", G, RST);
		if (right->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| R. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
	}
	fprintf(stderr, "%s====================================%s\n", G, RST);
} // 🖨️PRINT💥DEBUGING  // 🖨️PRINT💥DEBUGING  // 🖨️PRINT💥DEBUGING // 🖨️PRINT💥DEBUGING

int	ft_external(t_shell *s, t_env *env, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			exit(print_error(&s->numerr, errno));
		cmd_execution(s, env, node->data.s_exec.av);
	}
	else
	{
		s->child_pids[s->pid_count++] = pid;
		if (node->data.s_exec.fd_in != STDIN_FILENO)
			close(node->data.s_exec.fd_in);
	}
	return (0);
}

int	cmd_execution(t_shell *s, t_env *env, char **argv)
{
	char	**env_table;
	char	*path;

	path = path_making(env, argv[0]);
	if (!path)
	{
		w_free((void **)&path);
		print_custom_error(&s->numerr, 127, "Command not found");
		kill_children(s);
	}
	env_table = ltotable(env);
	if (!env_table)
	{
		w_free((void **)&path);
		print_error(&s->numerr, ENOMEM);
		kill_children(s);
	}
	if (execve(path, argv, env_table) == -1)
	{
		w_free((void **)&path);
		ft_free_char_array(env_table, count_var(env));
		print_custom_error(&s->numerr, 126, strerror(errno));
		kill_children(s);
	}
	return (0);
}

int	waiton(uint8_t *numerr, int *child_pids, int pid_count)
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
