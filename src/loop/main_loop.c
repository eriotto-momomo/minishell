/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:22:45 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/01 14:24:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_blank_line(char *line)
{
	while (*line)
	{
		if (!isspace((unsigned char)*line))
			return (0);
		line++;
	}
	return (1);
}

void	update_numerr(int *child_exit, uint8_t *numerr, int mode)
{
	if (mode == UPDATE_SIGNALS || mode == UPDATE_SIG_ERR)
	{
		if (g_sig == SIGINT)
			*numerr = 130;
		else if (g_sig == SIGQUIT)
			*numerr = 131;
	}
	if (mode == UPDATE_ERRNO || mode == UPDATE_SIG_ERR)
	{
		if (*child_exit == 1)
		{
			errno = *numerr;
			*child_exit = 0;
		}
		*numerr = errno;
	}
	g_sig = 0;
	errno = 0;
}

static void	reset(t_shell *s)
{
	if (!s->child_exit)
		s->numerr = 0;
	s->tmp_files_list = NULL;
	s->heredoc_count = 0;
	s->pipe_count = 0;
	s->pid_count = 0;
	s->tok_rdir = 0;
	s->tok_pipe = 0;
	s->tok_word = 0;
	s->heredoc_fd = -2;
	s->tmp_index = -1;
	reset_free(s);
}

static void	process_input(t_shell *s)
{
	if (lexer(s) != 0)
		return ;
	if (parser(s) != 0)
		return ;
	if (execution(s) != 0)
		return ;
}

void	prompt_loop(t_shell *s)
{
	rl_catch_signals = 0;
	reset(s);
	while (1)
	{
		update_numerr(&s->child_exit, &s->numerr, UPDATE_SIG_ERR);
		if (s->sig_mode != MINISHELL_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		update_numerr(&s->child_exit, &s->numerr, UPDATE_SIGNALS);
		if (s->line == NULL)
			terminate_shell(s);
		if (s->line && !is_blank_line(s->line))
		{
			add_history(s->line);
			process_input(s);
			fprintf(stderr, "global :%d\nsnumerr :%d\n", g_sig, s->numerr);
		}
		reset(s);
	}
	rl_catch_signals = 1;
}
