/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_arrayc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:32 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/29 17:13:53 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dup_array(char **source_arr, char **growed_arr, size_t arr_size)
{
	size_t	i;

	i = 0;
	while (i < arr_size)
	{
		growed_arr[i] = ft_strdup(source_arr[i]);
		if (!growed_arr[i] && i - 1 > 0)
		{
			ft_free_char_array(source_arr, i - 1);
			ft_free_char_array(growed_arr, i - 1);
			return (NULL);
		}
		w_free((void **)&source_arr);
		w_free((void **)&growed_arr);
		i++;
	}
	return (growed_arr);
}

char	**init_array(char **source_arr)
{
	source_arr = malloc(sizeof(char **) * 1);
	if (!source_arr)
		return (NULL);
	return (source_arr);
}

char	**grow_array(char **source_arr, size_t size)
{
	char	**growed_arr;
	size_t	arr_size;

	growed_arr = NULL;
	if (!source_arr)
		init_array(source_arr);
	arr_size = get_arr_size(source_arr);
	growed_arr = malloc(sizeof(char **) * size);
	if (!growed_arr)
		return (ft_free_char_array(source_arr, arr_size));
	growed_arr = dup_array(source_arr, growed_arr, arr_size);
	if (!growed_arr)
		return (NULL);
	ft_free_char_array(source_arr, arr_size);
	return (growed_arr);
}
