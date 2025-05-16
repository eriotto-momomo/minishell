/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:26:19 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 21:28:31 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_value(char *s)
{
	int		offset;
	char	*value;
	int		len;

	offset = 0;
	while (s[offset] && s[offset] != '=')
		offset++;
	if (!s[offset])
		return (ft_strdup(""));
	offset++;
	len = ft_strlen(s) - offset;
	value = malloc((len + 1) * sizeof(char));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &s[offset], len + 1);
	return (value);
}

char	*get_name(char *s)
{
	int		len;
	char	*name;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	name = malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, s, len + 1);
	return (name);
}


char	**ll_to_table(t_env *h_env)
{
	char	**table;
	t_env	*ptr;
	int		i;
	int		len;

	len = env_len(h_env);
	table = malloc(sizeof(char *) * (len + 1));
	if (!table)
		return (NULL);
	ptr = h_env;
	i = 0;
	while (ptr)
	{
		if (!ptr->value)
			ptr->value = "";
		table[i] = ft_strjoin(ptr->name, "=");
		if (!table[i])
			return (NULL); // Gérer l'erreur d'allocation
		
		char *tmp = table[i];
		table[i] = ft_strjoin(tmp, ptr->value);
		free(tmp);

		if (!table[i])
			return (NULL); // Gérer l'erreur d'allocation

		i++;
		ptr = ptr->next;
	}
	table[i] = NULL;
	return (table);
}


void	free_env_list(t_env **head)
{
	t_env *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		w_free((void **)&tmp->name);
		w_free((void **)&tmp->value);
		w_free((void **)&tmp);
	}
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
			free_env_list(&head);
			w_free((void **)&name);
			w_free((void **)&value);
			return (NULL);
		}
		add_var_back(&head, name, value);
		i++;
	}
	return (head);
}

