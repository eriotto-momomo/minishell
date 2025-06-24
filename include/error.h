/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:44:15 by timmi             #+#    #+#             */
/*   Updated: 2025/06/24 10:24:58 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int	print_error(uint8_t *numerr, int err);
int	print_custom_error(uint8_t *numerr, int err, char *error_m);

#endif
