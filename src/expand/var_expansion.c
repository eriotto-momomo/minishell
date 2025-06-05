/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/06/05 12:54:51 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	attribute_value(t_env *env, char **str, int i)
{
	char	*prefix;
	char	*sufix;

	prefix = make_prefix(env, *str, i);
	if (!prefix)
		return (0);
	i++;
	while ((*str)[i] && ft_isalnum((*str)[i]))
		i++;
	sufix = ft_substr(*str, i, ft_strlen(*str));
	if (!sufix)
	{
		free(prefix);
		return (0);
	}
	free(*str);
	*str = ft_strjoin(prefix, sufix);
	free(prefix);
	free(sufix);
	if (!*str)
		return (0);
	return (1);
}

char	*expand(t_env *env, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	while (tmp[i])
	{
		if (tmp[i] == '\'' && !is_in_double_quote(tmp, i))
		{
			i++;
			while (tmp[i] && (tmp[i] != '\'' && tmp[i] != '\"'))
				i++;
		}
		if (tmp[i] == '$')
		{
			if (!attribute_value(env, &tmp, i))
				return (NULL);
			i = 0;
		}
		else
			i++;
	}
	return (tmp);
}

int	var_expansion(t_env *env, char **s)
{
	char	*expanded;

	expanded = expand(env, *s);
	if (!expanded)
		return (0);
	free(*s);
	*s = expanded;
	return (1);
}
