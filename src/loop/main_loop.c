/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:22:45 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/23 15:59:36 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_numerr(t_shell *s)
{
	if (g_sig == SIGINT)
		s->numerr = 130;
	if (g_sig == SIGQUIT)
		s->numerr = 131;
}

static void	reset(t_shell *s)
{
	g_sig = 0;
	s->pipe_count = 0;
	s->pid_count = 0;
	s->tok_rdir = 0;
	s->tok_pipe = 0;
	s->tok_word = 0;
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
	setup_signals(s, MINISHELL_SIGNALS);
	reset(s);
	while (1)
	{
		//reset(s);
		if (s->sig_mode != MINISHELL_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		if (s->line == NULL)
			terminate_shell(s);
		if (s->line && *s->line)
		{
			update_numerr(s);
			add_history(s->line);
			process_input(s);
			reset(s);
		}
		update_numerr(s);
		reset(s);
	}
}
