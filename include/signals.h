/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/16 12:43:50 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/*
* L'enum 'e_signal' est utilisee pour indiquer le type de signal recu au shell par la
* variable globale 'g_sig'
* CTRLC = 'CTRL + C'
* CTRLD = 'CTRL + D'
* CTRLBACK = 'CTRL + \'
*/
enum e_signal
{
	DEFAULT_SIGNALS,	// Set `signals` to default usage
	MINISHELL_SIGNALS,	// Set `signals` related to minishell project
	CTRLC,
	CTRLD,
	CTRLBACK
};

// signals.c
void	setup_signals(t_shell *s, int mode);
int		exit_signal(void);

#endif
