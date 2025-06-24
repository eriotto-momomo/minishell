/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/24 18:07:20 by emonacho         ###   ########.fr       */
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
};

void	setup_signals(t_shell *s, int mode);
void	heredoc_handler(int signal);

#endif
