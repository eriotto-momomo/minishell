/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wft_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:42:42 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/04 17:41:07 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*wft_calloc(size_t nmemb, size_t size)
{
	char	*new_str;

	new_str = ft_calloc(nmemb, size);
	if (new_str == NULL)
	{
		ft_puterror("wft_calloc failed", strerror(errno));
		return (NULL);
	}
	return (new_str);
}
