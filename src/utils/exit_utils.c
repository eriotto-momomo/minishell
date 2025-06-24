/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/24 15:07:00 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *s, int ac, char **av)
{
	int	tmp;

	errno = 0;
	if (ac > 2)
		return (print_error(&s->numerr, E2BIG));
	if (ac > 1)
	{
		tmp = ft_atoi(av[1]);
		if (!tmp)
			print_error(&s->numerr, errno);
		s->numerr = (uint8_t)tmp;
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	terminate_shell(s);
	return (0);
}

void	reset_free(t_shell *s)
{
	if (s->head)
		free_token_list(&(s->head));
	if (s->root_node)
		free_ast(&(s->root_node));
	w_free((void **)&(s->line));
}

void	clean_free(t_shell *s)
{
	if (s->head)
		free_token_list(&(s->head));
	if (s->root_node)
		free_ast(&(s->root_node));
	if (s->env_list)
		free_env(&(s->env_list));
	w_free((void **)&(s->line));
	w_free((void **)&(s->prompt));
	w_free((void **)&(s->heredoc_tmp));
	setup_signals(s, DEFAULT_SIGNALS);
}

void	terminate_shell(t_shell *s)
{
	clean_free(s);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}

void	kill_children(t_shell *s)
{
	clean_free(s);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}

void	print_node(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;
	int i = 0;

	fprintf(stderr, "%s====================================%s\n", G, RST);
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
		fprintf(stderr, "%sprint_node%s| fd_in:  %d\n", B, RST, ast->data.s_exec.fd_in);
		fprintf(stderr, "%sprint_node%s| fd_out: %d\n", B, RST, ast->data.s_exec.fd_out);
		if (ast->data.s_exec.heredoc_count == 0)
			fprintf(stderr, "%sprint_node%s| %sNo heredoc to handle!%s\n", B, RST, R, RST);
		else if (ast->data.s_exec.heredoc_count > 0)
		{
			fprintf(stderr, "%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.s_exec.heredoc_count)
			{
				fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.heredoc_list[i], RST);
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

}

void	print_blocked_signals(void)
{
	sigset_t blocked;
	int i;

	if (sigprocmask(SIG_BLOCK, NULL, &blocked) == -1)
	{
		perror("sigprocmask");
		return;
	}

	printf("Signaux bloqués :\n");
	for (i = 1; i < NSIG; ++i)
	{
		if (sigismember(&blocked, i))
		{
			printf("  - Signal %d (%s)\n", i, strsignal(i));
		}
	}
}

void	print_pending_signals(void)
{
	sigset_t pending;
	int i;

	if (sigpending(&pending) == -1)
	{
		perror("sigpending");
		return;
	}

	printf("Signaux en attente :\n");
	for (i = 1; i < NSIG; ++i)
	{
		if (sigismember(&pending, i))
		{
			printf("  - Signal %d (%s)\n", i, strsignal(i));
		}
	}
}

