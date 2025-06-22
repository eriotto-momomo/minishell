/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 15:03:14 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_signals(t_shell *s)
{
	if ((g_sig == SIGINT || g_sig == SIGQUIT) && s->sig_mode == DEFAULT_SIGNALS)
	{
		if (g_sig == SIGINT)
			s->numerr = 130;
		if (g_sig == SIGQUIT)
			s->numerr = 131;

	}
	if (s->sig_mode == DEFAULT_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
	//if (g_sig == MINI_CTRLC)
	//	s->numerr = 130;
	//if (g_sig == MINI_BACKSLASH)
	//	s->numerr = 131;
}

void	exit_handler(int signal)
{
	g_sig = signal;
}

// 'CTRL + C' = SIGINT
void	sigint_handler(int signal)
{
	g_sig = signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// 'CTRL + \' = SIGQUIT
void	sigquit_ignore(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGQUIT, &act, NULL);
}

// 'CTRL + C' = SIGINT
// 'CTRL + \' = SIGQUIT
// 'CTRL + D' = EOF(pas vrmt un signal)
// 🚨 AJOUTER SAFE CHECKS
void	setup_signals(t_shell *s, int mode)
{
		struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (mode == MINISHELL_SIGNALS)
	{
		sigquit_ignore();
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
		s->sig_mode = MINISHELL_SIGNALS;
	}
	else if (mode == DEFAULT_SIGNALS)
	{
		act.sa_handler = &exit_handler;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = DEFAULT_SIGNALS;
	}
}
