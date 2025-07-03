/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/25 16:35:10 by timmi            ###   ########.fr       */
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
int		handle_termios(t_shell *s, int mode);

#endif
