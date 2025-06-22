/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:13:43 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 17:06:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

enum e_signal
{
	READY,
	CLEAN_EXIT,
	DEFAULT_SIGNALS,
	MINISHELL_SIGNALS
};

void	setup_signals(t_shell *s, int mode);

#endif
