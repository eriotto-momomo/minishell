/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arr_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:25:30 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:01 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_arr_size(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while(1)
	{
		if (arr[i])
			i++;
		else
			break ;
	}
	if (i > 0)
		return (i - 2);
	else
		return (0);
}
