/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:22:45 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/19 14:11:23 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	reset(t_shell *s)
{
	s->pipe_count = 0;
	s->pid_count = 0;
	w_free((void **)&s->line);
}

static void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
	reset(s);
}

void prompt_loop(t_shell *s)
{
	setup_signals(&s, MINISHELL_SIGNALS);
	while (1)
	{
		if (s->sig_mode == DEFAULT_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		if (s->line == NULL)
			terminate_shell(s, 0);
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
		}
		reset(s);
	}
}
