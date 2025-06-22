/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:44:15 by timmi             #+#    #+#             */
/*   Updated: 2025/06/22 17:05:03 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int	print_error(uint8_t *numerr, int err, char *f);
int	print_custom_error(uint8_t *numerr, int err, char *error_m);

#endif
