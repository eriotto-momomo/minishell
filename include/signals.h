/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/05 17:17:16 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

enum e_signal
{
	DEFAULT_SIGNALS,
	MINISHELL_SIGNALS,
	HEREDOC_SIGNALS,
	UPDATE_ERRNO,
	UPDATE_SIGNALS,
	UPDATE_SIG_ERR,
};

void	setup_signals(t_shell *s, int mode);
void	heredoc_handler(int signal);

#endif
