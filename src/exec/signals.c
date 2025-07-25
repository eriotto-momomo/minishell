/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/25 15:20:31 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_handler(int signal)
{
	char	c;

	g_sig = signal;
	c = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &c);
}

void	clean_exit_handler(int signal)
{
	g_sig = signal;
	if (signal == SIGQUIT)
		write(2, "Quit (core dumped)", 18);
	write(1, "\n", 1);
}

void	sigint_handler(int signal)
{
	g_sig = signal;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
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
		signal(SIGQUIT, SIG_IGN);
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
		signal(SIGQUIT, SIG_IGN);
		s->sig_mode = HEREDOC_SIGNALS;
	}
}
