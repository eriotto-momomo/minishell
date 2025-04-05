/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_calloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:42:42 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 20:49:06 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Call with: `[PTR] = w_calloc([NMEMB], [SIZE]);`
void	*w_calloc(size_t nmemb, size_t size)
{
	char	*new_str;

	new_str = ft_calloc(nmemb, size);
	if (new_str == NULL)
	{
		ft_puterror("w_calloc failed", strerror(errno));
		return (NULL);
	}
	return (new_str);
}
