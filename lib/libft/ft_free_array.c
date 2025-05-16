/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:57 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/16 21:39:10 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_array(void *array, int size, char mode)
{
	int		i;
	int		*int_array;
	char	**char_array;

	i = 0;
	if (mode == 'i')
	{
		int_array = (int *)array;
		free(int_array);
	}
	else if (mode == 'c')
	{
		char_array = (char **)array;
		while (i < size)
		{
			if (char_array[i] != NULL)
			{
				w_free((void **)&char_array[i]);
				char_array[i] = NULL;
			}
			i++;
		}
		w_free((void **)&char_array);
	}
	return (NULL);
}
