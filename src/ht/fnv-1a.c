/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnv-1a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:49:14 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/07 20:56:15 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

uint64_t	hash_key(const char *key)
{
	const char	*p;
	uint64_t hash;

	p = key;
	hash = FNV_OFFSET;
	while (*p)
	{
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
		p++;
	}
	return hash;
}