/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:35:57 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/16 19:00:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

// FORWARD DECLARATION (dis au compilateur que "t_shell" existe)
typedef struct s_shell	t_shell;

void	prompt_loop(t_shell *s);

/**
 * @brief	Create a shell prompt using the user's name and the host name.
 *
 * @details	This function retrieves the current user's name and the hostname from
 *			the env variables. If the hostname isn't available, it attempts
 *			to use the session manager name instead, trimming it if necessary.
 *			The prompt is then built by combining the user and host/session name.
 *			If neither is available, a default prompt "minishell-1.0" is used.
 *
 * @return	A dynamically allocated string containing the full shell prompt.
 *			The caller is responsible for freeing it.
 */
void	create_prompt(t_shell *s);
void	reset_prompt(t_shell *s, int mode);

#endif
