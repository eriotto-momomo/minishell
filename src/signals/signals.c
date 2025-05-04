/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/04 13:44:00 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	sig_handler(int signal, siginfo_t *info, void *more_info)
{
	(void)info;
	(void)more_info;
	printf("sig_handler | signal = %d\n", signal);
	return ;
}

void get_signals(t_shell *s)
{
	(void)s;
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT); // 'CTRL + C'
	//sigdelset(&sa.sa_mask, SIGQUIT); // 'CTRL + \'
	printf("get_signals | %sEXIT get_signals%s\n", G, RST);
}
