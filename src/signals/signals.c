/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 11:59:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_handler(int signal)
{
	g_sig = signal;
}

void	clean_exit_handler(int signal)
{
	g_sig = signal;
}

void	sigint_handler(int signal)
{
	g_sig = signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signal)
{
	g_sig = signal;
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(t_shell *s, int mode)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (mode == MINISHELL_SIGNALS)
	{
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
		act.sa_handler = &sigquit_handler;
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = MINISHELL_SIGNALS;
	}
	else if (mode == DEFAULT_SIGNALS)
	{
		act.sa_handler = &clean_exit_handler;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = DEFAULT_SIGNALS;
	}
	else if (mode == HEREDOC_SIGNALS)
	{
		act.sa_handler = &heredoc_handler;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = HEREDOC_SIGNALS;
	}
}
