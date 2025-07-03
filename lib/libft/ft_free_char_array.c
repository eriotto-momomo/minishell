/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:25:38 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 19:11:11 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_char_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i] != NULL)
		{
			w_free((void **)&array[i]);
			array[i] = NULL;
		}
		i++;
	}
	w_free((void **)&array);
	return (NULL);
}
