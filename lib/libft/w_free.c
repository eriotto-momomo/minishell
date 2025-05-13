/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:21:57 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/30 09:21:53 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Call with: `w_free((void **)&char_str)`
void	w_free(void **ptr)
{
	// if (ptr == NULL || *ptr == NULL)
	// 	ft_puterror("w_free warning", "Trying to free a NULL pointer.");
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
