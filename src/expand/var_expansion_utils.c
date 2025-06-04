/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:18:49 by timmi             #+#    #+#             */
/*   Updated: 2025/06/03 10:33:10 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_double_quote(char *s, int j)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	while (i < j && s[i])
	{
		if (s[i] == '\"')
			in_double = !in_double;
		i++;
	}
	return (in_double);
}
