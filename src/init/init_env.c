/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:26:19 by timmi             #+#    #+#             */
/*   Updated: 2025/05/08 21:30:28 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_name(char	*s)
{
	int		i;
	size_t	len;
	char	*name;

	i = 0;
	len = 0;
	while (s[len] != '=')
		len++;
	name = malloc((len + 1) *  sizeof(char));
	if (!name)
		return (NULL);
	while (i < (int)len)
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return(name);
}

char	*get_value(char *s)
{
	int		i;
	int		offset;
	char	*value;
	
	offset = 0;
	while (s[offset] && s[offset] != '=')
		offset++;
	offset++;
	value = malloc((ft_strlen(s) - offset + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	while (s[offset])
		value[i++] = s[offset++];
	value[i] = '\0';
	return(value);
}

t_env	*table_to_ll(char **env)
{
	int		i;
	t_env	*head;
	char	*name;
	char	*value;

	i = 0;
	head = NULL;
	while (env[i])
	{
		name = get_name(env[i]);
		value = get_value(env[i]);
		if (!name || !value)
		{
			// FRE EVERYHTING
			w_free((void **)&name);
			w_free((void **)&value);
			return (NULL);
		}
		add_var_back(&head, name, value);
		i++;
	}
	return (head);
}
