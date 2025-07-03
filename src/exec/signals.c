/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/01 16:24:49 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_termios(t_shell *s, int mode)
{
	fprintf(stderr, "%s%s%s\n", P, "handle_termios | ENTER FUNCTION", RST);
	if (mode == 0)
	{
		if (tcgetattr(STDIN_FILENO, &s->term_backup) == -1)
			return (print_error(&s->numerr, errno));
	}
	else if (mode == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &s->term_backup) == -1)
			return (print_error(&s->numerr, errno));
	}
	return (0);
}

void	heredoc_handler(int signal)
{
	g_sig = signal;
	close(STDIN_FILENO);
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
	write(STDOUT_FILENO, "\n", 1);
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
