/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:19 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 16:34:35 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_quote(char *s)
{
	size_t	c;
	int		i;
	int		in;
	char	q;

	i = 0;
	in = 0;
	c = 0;
	q = '\0';
	while (s[i])
	{
		if (!in && ft_isquote(s[i]))
		{
			c++;
			in = 1;
			q = s[i];
		}
		else if (in && s[i] == q)
		{
			c++;
			in = 0;
		}
		i++;
	}
	return (c);
}

static int trim_quote(char **s)
{
	char	quote;
	int		i;
	int		j;
	char	*new_s;

	if (!s || !*s)
		return (-1);
	new_s = malloc(sizeof(char) * (ft_strlen(*s) - count_quote(*s) + 1));
	if (!new_s)
		return (-1);
	i = 0;
	j = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' || (*s)[i] == '\"')
		{
			quote = (*s)[i++];
			while ((*s)[i] && (*s)[i] != quote)
				new_s[j++] = (*s)[i++];
		}
		else
			new_s[j++] = (*s)[i++];
	}
	new_s[j] = '\0';
	v_switch(s, new_s);
	return (0);
}


static int	shrink_array(char ***arr, int ac, int i)
{
	int		j;
	int		k;
	char	**new_arr;

	new_arr = malloc(sizeof(char *) * ac);
	if (!new_arr)
		return (1);
	j = 0;
	k = 0;
	while (j < ac)
	{
		if (j != i)
		{
			new_arr[k] = (*arr)[j];
			k++;
		}
		else
			free((*arr)[j]);
		j++;
	}
	new_arr[k] = NULL;
	free(*arr);
	*arr = new_arr;
	return (0);
}

int	string_processing(t_shell *s, int *ac, char ***args)
{
	int		i;

	i = 0;
	while (i < *ac)
	{
		if (ft_strchr((*args)[i], '$'))
		{
			if (!expand(s->env_list, &(*args)[i]))
				return (0);
			if ((*args)[i][0] == '\0')
			{
				if (shrink_array(args, *ac, i) == 1)
					return (0);
				*ac = *ac - 1;
				continue ;
			}
		}
		if ((*args)[i] && (ft_strchr((*args)[i], '\'') || ft_strchr((*args)[i], '\"')))
			if (trim_quote(&(*args)[i]) == -1)
				return (0);
		i++;
	}
	return (1);
}
