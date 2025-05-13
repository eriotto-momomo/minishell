/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/05/13 11:47:55 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static char 	*get_var(char *s)
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
	while (s[start] && !ft_is_space(s[start]) && !is_sep(s[start]))
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

int	is_in_env(t_env	*env, char *var)
{
	while (env)
	{
		if (ft_strncmp(env->name, var, ft_strlen(var)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
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

static char 	*replace(t_env *env, char *str, char *value)
{
	int		i;
	char	*prefix;
	char	*join;
	char	*rest;
	
	prefix = dup_prefix(str);
	if (!prefix)
		return (NULL);
	if (value)
	{
		join = ft_strjoin(prefix, ft_getenv(env, value));
		free(prefix);
		free(value);
		i = ft_strlen(join);
		rest = ft_substr(str, i, ft_strlen(str));
		prefix = ft_strjoin(join, rest);
		return (prefix);
	}
	free(prefix);
	return (NULL);
}

void	expand(t_env *env, char *str)
{
	char	*var;
	char	*r_str;
	
	if (!ft_strchr(str, '$'))
		return ;
	var = get_var(str);
	if (is_in_env(env, var))
	{
		r_str = replace(env, str, var);
		if (r_str)
		{
			free(str);
			str = r_str;
		}
		else
			return ;
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
		expand(s->env_list, args[i++]);
	printf("finished!\n");
	
}
