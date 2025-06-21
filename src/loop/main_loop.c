/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:22:45 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/21 17:33:55 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	reset(t_shell *s)
{
	s->pipe_count = 0;
	s->pid_count = 0;
	s->numerr = 0;
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

void prompt_loop(t_shell *s)
{
	setup_signals(s, MINISHELL_SIGNALS);
	reset(s);
	while (1)
	{
		if (s->sig_mode == DEFAULT_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		if (s->line == NULL)
			terminate_shell(s);
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
			reset(s);
		}
		reset(s);
	}
}
