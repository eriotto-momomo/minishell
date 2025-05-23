/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_kill.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:17:53 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 19:42:58 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	w_kill(pid_t pid, int signal)
{
	if (kill(pid, signal) < 0)
		ft_puterror("w_kill failed", strerror(errno));
}
