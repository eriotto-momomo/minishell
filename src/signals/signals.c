/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/19 13:48:13 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// ATTENTION A QUITTER PROPREMENT AVEC UN SIGINT DANS UN FORK
// ATTENTION A QUITTER PROPREMENT AVEC UN SIGINT DANS UN FORK
// ATTENTION A QUITTER PROPREMENT AVEC UN SIGINT DANS UN FORK

int	exit_signal(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char *) * 3);
	if (!buffer)
		return (1);
	read(2, buffer, 3);
	if (ft_strncmp(buffer, "^D", ft_strlen(buffer)))
	{
		printf("exit_signal | buffer: %s\n", buffer);			// 🖨️PRINT💥DEBUGING
		return (1);
	}
	return (0);
}

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
	printf("%s%s", P, "setup_signals | ");				// 🖨️PRINT💥DEBUGING
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (mode == MINISHELL_SIGNALS)
	{
		printf("SIGNALS in MINISHELL mode%s\n", RST);	// 🖨️PRINT💥DEBUGING
		sigquit_ignore();
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
		s->sig_mode = MINISHELL_SIGNALS;
	}
	else if (mode == DEFAULT_SIGNALS)
	{
		printf("SIGNALS in DEFAULT mode%s\n", RST);		// 🖨️PRINT💥DEBUGING
		act.sa_handler = &clean_exit_handler;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		s->sig_mode = DEFAULT_SIGNALS;
	}
}
