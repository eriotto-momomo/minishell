/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:18:49 by timmi             #+#    #+#             */
/*   Updated: 2025/06/05 12:06:00 by timmi            ###   ########.fr       */
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

char	*make_prefix(t_env *env, char *str, int i)
{
	char	*value;
	char	*prefix;
	char	*ret;

	value = get_var(env, str + i + 1);
	if (!value)
		return (NULL);
	prefix = ft_substr(str, 0, i);
	if (!prefix)
	{
		free(value);
		return (NULL);
	}
	ret = ft_strjoin(prefix, value);
	free(prefix);
	free(value);
	return (ret);
}
char	*get_var(t_env *env, char *s)
{
	int		end;
	char	*var_name;
	char	*var_val;

	end = 0;
	while (s[end] && (ft_isalnum(s[end])))
		end++;
	var_name = ft_substr(s, 0, end);
	if (!var_name)
		return (NULL);
	var_val = ft_strdup(ft_getenv(env, var_name));
	free(var_name);
	if (var_val)
		return (var_val);
	free(var_val);
	return (ft_strdup(""));
}
