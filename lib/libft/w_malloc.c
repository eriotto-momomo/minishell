/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:27:26 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 20:49:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Call with: `w_malloc((void **)&[PTR], [SIZE]);`
void	w_malloc(void **ptr, size_t size)
{
	if (size <= 0)
	{
		*ptr = NULL;
		ft_puterror("w_malloc failed",
			"`size` must be a non-zero positive value.");
		return ;
	}
	*ptr = malloc(size);
	if (*ptr == NULL)
	{
		errno = ENOMEM;
		ft_puterror("w_malloc failed", strerror(errno));
	}
}
