/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnprefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:11:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/04/22 11:13:32 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Checks if a string starts with a given prefix up to a maximum length.
 *
 * This function compares the beginning of the string `str` with the string `prefix`
 * for up to `len` characters. If all characters in `prefix` match the corresponding
 * characters in `str` up to `len`, the function returns a pointer to the character
 * in `str` immediately following the prefix. If the prefix does not match,
 * the function returns NULL.
 *
 * @param str The string to be checked.
 * @param prefix The prefix to compare against.
 * @param len The maximum number of characters to compare.
 *
 * @return A pointer to the character in `str` after the matched prefix,
 *         or NULL if `prefix` is not a prefix of `str` within `len` characters.
 */
char *ft_strnprefix(char *str, char *prefix, size_t len)
{
	size_t i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == prefix[i])
			i++;
		else
			return (NULL);
	}
	return ((char *)str + i);
}
