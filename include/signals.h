/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/19 13:47:44 by emonacho         ###   ########.fr       */
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
	CLEAN_EXIT,
};

// signals.c
void	setup_signals(t_shell *s, int mode);
int		exit_signal(void);

#endif
