/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:18:49 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 17:50:38 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_env(t_env	*env, char *var)
{
	if (!var)
		return (0);
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

size_t	offset_calc(char *str)
{
	size_t	offset;

	offset = 0;
	while (str[offset] && str[offset] != '$')
		offset++;
	return (offset);
}
