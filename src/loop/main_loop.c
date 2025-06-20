/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:22:45 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/20 10:12:28 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	reset(t_shell *s)
{
	s->pipe_count = 0;
	s->pid_count = 0;
	s->numerr = 0;
	w_free((void **)&s->line);
}

static void	process_input(t_shell *s)
{
	if (lexer(s) != 0)
	{
		clean_free(s);
		return ;
	}
	if (parser(s) != 0)
	{
		clean_free(s);
		return ;	
	}
	if (execution(s) != 0)
	{
		clean_free(s);
		return ;
	}
	reset(s);
}

void prompt_loop(t_shell *s)
{
	setup_signals(s, MINISHELL_SIGNALS);
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
		}
		reset(s);
	}
}
