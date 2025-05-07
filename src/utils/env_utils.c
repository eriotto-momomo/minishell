/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:13:49 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/07 22:41:48 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_dup(char **array)
{
	int		i;
	char	**copy;
	
	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			free_str_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_getenv(char **env, const char *name)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
		{
			value = ft_strchr(env[i], '=');
			if (!value)
				return (NULL);
			value++;
			return (value);
		}
		i++;
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
