/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/16 13:13:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_signal(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char *) * 3);
	if (!buffer)
		return (1);
	read(2, buffer, 3);
	if (ft_strncmp(buffer, "^D", ft_strlen(buffer)))
	{
		printf("exit_signal | buffer: %s\n", buffer);
		return (1);
	}
	return (0);
}

int	setup_termios(t_shell *s, int mode)
{
	if (mode == MINISHELL_SIGNALS)
	{
		tcgetattr(0, &s->old_termios);
		s->new_termios = s->old_termios;
		s->new_termios.c_cc[VEOF] = 3;	// attribue EOF a CTRL+C
		s->new_termios.c_cc[VINTR] = 4;	// attribue SIGINT a CTRL+D
		tcsetattr(0, TCSANOW, &s->new_termios);
	}
	else if (mode == DEFAULT_SIGNALS)
	{
		tcsetattr(0,TCSANOW,&s->old_termios);
	}
	return (0);
}

// 'CTRL + C' = SIGINT remplace par 'CTRL + D'
void	sigint_handler(int signal)
{
	(void)signal;
	//ft_putstr_fd("sigint_handler | SIGINT CATCHED!\n", 1);
	write(1, "\n^D\n", 4);
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
void	setup_signals(t_shell *s, int mode)
{
	struct sigaction	act;

	printf("%s%s", P, "setup_signals | ");
	if (mode == MINISHELL_SIGNALS)
	{
		// 🚨 AJOUTER SAFE CHECKS
		printf("SIGNALS in MINISHELL mode%s\n", RST);
		sigquit_ignore();
		//act.sa_handler = &sigint_handler;	// 🚨USELESS❔
		//sigaction(SIGINT, &act, NULL);			// 🚨USELESS❔
		setup_termios(s, MINISHELL_SIGNALS);
		s->sig_mode = MINISHELL_SIGNALS;
	}
	else
	{
		// 🚨 AJOUTER SAFE CHECKS
		printf("SIGNALS in DEFAULT mode%s\n", RST);
		act.sa_handler = SIG_DFL;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		setup_termios(s, DEFAULT_SIGNALS);
		s->sig_mode = DEFAULT_SIGNALS;
	}
}
