/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/06/20 17:32:04 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	attribute_value(t_env *env, char **str, int i)
{
	char	*prefix;
	char	*sufix;
	char	*tmp;

	prefix = make_prefix(env, *str, i);
	if (!prefix)
		return (1);
	i++;
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '?'))
		i++;
	sufix = ft_substr(*str, i, ft_strlen(*str));
	if (!sufix)
	{
		free(prefix);
		return (1);
	}
	tmp = ft_strjoin(prefix, sufix);
	free(prefix);
	free(sufix);
	if (!tmp)
		return (1);
	free(*str);
	*str = tmp;
	return (0);
}

int	expand(t_env *env, char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !is_in_double_quote((*str), i))
		{
			i++;
			while ((*str)[i] && ((*str)[i] != '\''))
				i++;
		}
		if ((*str)[i] == '$')
		{
			if (attribute_value(env, str, i) != 0)
				return (1);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}
