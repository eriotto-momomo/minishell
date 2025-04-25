/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:47:42 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 14:14:12 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_tab(void *tab, int mode)
{
	int		*int_tab;
	char	**char_tab;
	size_t	len;
	
	len = 0;
	if (mode)
	{
		int_tab = (int *)tab;
		while (int_tab[len])
			len++;
		return (len);
	}
	char_tab = (char **)tab;
	while (char_tab[len])
		len++;
	return (len);
}
