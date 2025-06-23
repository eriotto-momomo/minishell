/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:19 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 20:20:26 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_quote(char *s)
{
	size_t	c;
	int		i;
	char	q;

	i = 0;
	c = 0;
	q = '\0';
	while (s[i])
	{
		if (q == 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			q = s[i++];
			c++;
		}
		if (s[i] == q)
		{
			c++;
			q = '\0';
		}
		i++;
	}
	return (c);
}

int	trim_quote(char **s, int i, int j)
{
	char	quote;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(*s) - count_quote(*s) + 1));
	if (!new_s)
		return (1);
	quote = '\0';
	while ((*s)[i])
	{
		if (quote == '\0' && ((*s)[i] == '\'' || (*s)[i] == '\"'))
			quote = (*s)[i++];
		if ((*s)[i] != quote)
			new_s[j++] = (*s)[i++];
		else
			i++;
		if ((*s)[i] && (*s)[i] == quote)
		{
			quote = '\0';
			i++;
		}
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
			if (expand(s->numerr, s->env_list, &(*args)[i]) != 0)
				return (print_error(&s->numerr, errno, "expand"));
			if ((*args)[i][0] == '\0')
			{
				if (shrink_array(args, *ac, i) == 1)
					return (0);
				*ac = *ac - 1;
				continue ;
			}
		}
		if ((*args)[i] && (ft_strchr((*args)[i], '\'')
			|| ft_strchr((*args)[i], '\"')))
			if (trim_quote(&(*args)[i], 0, 0) != 0)
				return (print_error(&s->numerr, errno, "trim_quote"));
		printf("%s\n", (*args)[i]);
		i++;
	}
	return (0);
}
