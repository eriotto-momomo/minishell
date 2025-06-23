/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:45:07 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 12:06:19 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H
/**
 * @brief Initializes and runs the main loop of the shell.
 *
 * Continuously displays the shell prompt, reads user input,
 * processes non-empty lines, and resets the shell state after each iteration.
 * Uses GNU readline for input and history management.
 * The loop runs indefinitely until the program is externally terminated
 * or exits from within `process_input()`.
 *
 * @param s Pointer to the shell state structure (t_shell),
 *          containing prompt string, input line, and context
 *          needed for parsing and execution.
 */
void	prompt_loop(t_shell *s);
void	update_numerr(t_shell *s);

#endif
