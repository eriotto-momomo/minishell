/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/08 22:39:07 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

volatile sig_atomic_t	g_sig;

int	sig_catcher(void)
{
	if (g_sig == 2) // 'CTRL + C' = SIGINT
	{
		printf("sig_catcher | %sg_sig = %d (SIGINT)%s\n", Y, g_sig, RST);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 0;
		return (1);
	}
	return (0);
}


void	sig_handler(int signal, siginfo_t *info, void *more_info)
{
	(void)info;
	(void)more_info;
	g_sig = signal;
	printf("sig_handler | %sg_sig = %d%s\n", Y, g_sig, RST);
}

// 'CTRL + C' = SIGINT
// 'CTRL + \' = SIGQUIT
// 'CTRL + D' = EOF(pas vrmt un signal)
void	sig_setup(void)
{
	struct sigaction	sa;

	g_sig = 0;
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	signal(SIGQUIT, SIG_IGN);			// Ignore 'CTRL + \'
	sigaction(SIGINT, &sa, NULL);		// Relance un prompt
}
