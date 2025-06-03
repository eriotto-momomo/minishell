/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/06/03 10:17:31 by timmi            ###   ########.fr       */
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
	while (s[end] && (ft_isalnum(s[end]) || ft_isalpha(s[end])))
		end++;
	var_name = ft_substr(s, 0, end);
	if (!var_name)
		return (NULL);
	var_val = ft_getenv(env, var_name);
	if (var_val)
		return (var_val);
	return ("");
}

int	replace(t_env *env, char *str, int	i)
{
	char	*value;
	char	*prefix;
	char	*post;
	char	*ret_s;
	
	value = get_var(env, str + i + 1); // Check if the name of the var is in the env and then return its value, if not return an empty string.
	if (!value)
		return (0);
	prefix = ft_substr(str, 0, i);
	i++; // skip $ sign
	while (str[i] && (ft_isalnum(str[i]) || ft_isalnum(str[i])))
		i++;
	post = ft_substr(str, i, ft_strlen(str));
	ret_s = triple_join(prefix, value, post);
	if (!ret_s)
	{
		free(prefix);
		free(post);
		return (0);
	}
	printf("ret :%s\n", ret_s);
	return (1);
}

int	expand(t_env *env, char **str)
{
	int		i;
	int		in_quote;
	char	quote;
	char	*ptr;

	i = 0;
	in_quote = 0;
	ptr = *str;
	while (ptr[i])
	{
		if (ft_isquote(ptr[i]) && !in_quote) // Check si on rentre dans un quote
		{
			printf("Entering quote\n");
			in_quote = 1;
			quote = ptr[i++]; // sauvegarde le type de quote
		}
		else if (ft_isquote(ptr[i]) && in_quote) // Check si on sort d'un quote
		{
			printf("Leaving quote\n");
			in_quote = 0;
			i++;
		}
		while (ptr[i] && quote == '\'' && in_quote) // Skip si on est dans un single quote
			i++;
		if (ptr[i] == '$') // Si on rencontre une var -> on remplace
			replace(env, ptr, i);
		i++;
	}
	return (1);
}

