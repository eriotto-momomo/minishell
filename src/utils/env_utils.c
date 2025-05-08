/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:13:49 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 17:52:11 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <assert.h>

void	free_env(t_env **h_env)
{
	t_env	*current;
	t_env	*temp;

	if (!h_env || !*h_env)
		return ;
	current = *h_env;
	while (current)
	{
		temp = current->next;
		w_free((void **)&(current->name));
		w_free((void **)&(current->value));
		w_free((void **)&current);
		current = temp;
	}
	*h_env = NULL;
}

char	*ft_getenv(t_env *h_env, const char *name)
{
	t_env	*temp;
	
	temp = h_env;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(name)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env *create_var(char *name, char	*value)
{
	t_env	*new_node;

	new_node = (t_env*)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void add_var_back(t_env **head, char *name, char *value)
{
    t_env	*new_node = create_var(name, value);
	t_env	*temp;

	if (*head == NULL)
	{
        *head = new_node;
        return;
    }
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	del_var(t_env **head, t_env **target)
{
	if (*target == NULL)
		return ;
	if ((*target)->prev)
		(*target)->prev->next = (*target)->next;
	else
		*head = (*target)->next;
	if ((*target)->next)
		(*target)->next->prev = (*target)->prev;
	w_free((void **)&(*target)->name);
	w_free((void **)&(*target)->value);
	w_free((void **)&(*target));
}

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