/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/06/03 14:07:10 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*triple_join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;
	
	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	free(s1);
	free(s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	free(s3);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*get_var(t_env *env, char *s)
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

static int	attribute_value(t_env *env, char **str, int i)
{
	char	*value;
	char	*prefix;
	char	*post;
	char	*ret_s;

	value = get_var(env, *str + i + 1);
	if (!value)
		return (0);
	prefix = ft_substr(*str, 0, i);
	i++;
	while ((*str)[i] && ft_isalnum((*str)[i]))
		i++;
	post = ft_substr(*str, i, ft_strlen(*str));
	ret_s = triple_join(prefix, value, post);
	if (!ret_s)
	{
		free(prefix);
		free(post);
		return (0);
	}
	free(*str);
	*str = ret_s;
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
		if (tmp[i++] == '\'')
			while (tmp[i] && tmp[i] != '\'')
				i++;
		if (tmp[i] == '$')
		{
			attribute_value(env, &tmp, i);
			i = 0;
		}
		else
			i++;
	}
	return (tmp);
}

int	var_expansion(t_env * env, char **s)
{
	char	*expanded;

	expanded = expand(env, *s);
	if (!expanded)
	{
		printf("expanpded is NULL");
		exit(1);
	}
	free(*s);
	*s = expanded;
	return (1);
}
