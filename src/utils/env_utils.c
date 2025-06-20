/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:13:49 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/20 20:59:59 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if ((ft_strlen(name) == ft_strlen(temp->name))
			&& (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0))
				return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*create_var(char *name, char	*value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	add_var_back(t_env **head, char *name, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_var(name, value);
	if (!new_node)
		return (0);
	if (*head == NULL)
	{
		*head = new_node;
		return (1);
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
	return (1);
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
