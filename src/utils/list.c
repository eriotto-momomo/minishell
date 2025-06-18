/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:27 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 10:57:35 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *create_node(char *data)
{
	t_token	*new_node;

	new_node = (t_token*)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->type = get_token_id(data);
	/* new_node->type = get_token(new_node->data);  A voir */
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	add_back(t_token **head, char *data)
{
    t_token	*new_node;
	t_token	*temp;

	// if (ft_strncmp(data, "", 1) == 0)
	// 	return (1);
	new_node = create_node(data);
	if (!new_node)
		return (0);
	if (*head == NULL)
	{
        *head = new_node;
        return 1;
    }
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
	return (1);
}

void free_list(t_token **head)
{
	t_token *current;
	t_token *temp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		// printf("freeing -> %s\n", (*head)->data);
		temp = current->next;
		w_free((void **)&(current->data));
		w_free((void **)&current);
		current = temp;
	}
	*head = NULL;
}


size_t count_cmd(t_token *head)
{
	size_t	c;
	t_token	*temp;

	c = 1;
	temp = head;
	while (temp)
	{
		if (temp->type == PIPE)
			c++;
		temp = temp->next;
	}
	return (c);
}

size_t	env_len(t_env *h_env)
{
	size_t	len;
	t_env	*temp;

	len = 0;
	temp = h_env;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
