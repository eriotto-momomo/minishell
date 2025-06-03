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
	var_val = ft_getenv(env, var_name);
	if (var_val)
		return (var_val);
	return ("");
}

static char	*attribute_value(t_env *env, char **str, int i)
{
	char	*value;
	char	*prefix;
	char	*post;
	char	*ret_s;
	
	value = get_var(env, *str + i + 1);
	if (!value)
		return (NULL);
	prefix = ft_substr(*str, 0, i);
	while (*str[i] && ft_isalnum(*str[i]))
		i++;
	printf("%s\n", *str+i);
	post = ft_substr(*str, i, ft_strlen(*str));
	ret_s = triple_join(prefix, value, post);
	if (!ret_s)
	{
		free(prefix);
		free(post);
		return (NULL);
	}
	printf("ret :%s\n", ret_s);
	return (ret_s);
}

char	*expand(t_env *env, char *str)
{
	int		i;
	char	*ret;
	// char	*tmp;

	(void)env;
	i = 0;
	ret = ft_calloc(2, 1);
	while (str[i])
	{
		if (ft_isquote(str[i])) // Check si on rentre dans un quote
		{
			if (str[i++] == '\'')
				while (str[i] && str[i] != '\'')
					i++;
		}
		if (str[i] == '$')
		{
			attribute_value(env, &str, i);
		}
		i++;
	}
	printf("%s\n", str);
	exit(1);
	return (ret);
}

int	var_expansion(t_env * env, char **s)
{
	char	*expanded;

	expanded = expand(env, *s);
	if (!expanded)
		return (0);
	free(*s);
	*s = expanded;
	return (1);
}
