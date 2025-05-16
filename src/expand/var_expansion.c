/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 19:03:18 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_var(char *s)
{
	char	*ret;
	int		start;
	int		i;

	start = 0;
	i = 0;
	while (s[start] && s[start] != '$')
		start++;
	i = ++start;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	ret = malloc((i - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[start] && !ft_isspace(s[start]) && !is_sep(s[start]))
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

static char	*dup_prefix(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*replace(t_env *env, char *str, char *value)
{
	int		i;
	char	*prefix;
	char	*join;
	char	*rest;

	prefix = dup_prefix(str);
	if (!prefix)
		return (NULL);
	if (env)
		join = ft_strjoin(prefix, ft_getenv(env, value));
	else
		join = ft_strjoin(prefix, "");
	free(prefix);
	if (!join)
		return (NULL);
	i = (int)offset_calc(str) + ft_strlen(value);
	rest = ft_substr(str, i + 1, ft_strlen(str));
	if (rest)
		prefix = ft_strjoin(join, rest);
	else
		free(prefix);
	free(join);
	free(rest);
	return (prefix);
}

void	expand(t_env *env, char **str)
{
	char	*var;
	char	*r_str;

	if (!ft_strchr(*str, '$'))
		return ;
	var = get_var(*str);
	if (is_in_env(env, var))
		r_str = replace(env, *str, var);
	else
		r_str = replace(NULL, *str, var);
	free(var);
	if (r_str)
	{
		free(*str);
		*str = r_str;
	}
	else
		return ;
	expand(env, str);
}

void	var_expansion(t_shell *s, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		expand(s->env_list, &args[i++]);
	}
}
