/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 18:11:04 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit_handler(int signal)
{
	(void)signal;
	g_status = CLEAN_EXIT;
}

// 'CTRL + C' = SIGINT
void	sigint_handler(int signal)
{
	(void)signal;
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
		act.sa_handler = &clean_exit_handler;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = DEFAULT_SIGNALS;
	}
}
