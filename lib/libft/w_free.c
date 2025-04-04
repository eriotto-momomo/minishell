/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:21:57 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 20:49:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Call with: `w_free((void **)&char_str)`
void	w_free(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		ft_puterror("w_free warning", "Trying to free a NULL pointer.");
	else if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
