/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:27 by timmi             #+#    #+#             */
/*   Updated: 2025/05/02 10:47:20 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *create_node(char *data)
{
	t_list	*new_node;

	new_node = (t_list*)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->type = get_token_id(data);
	/* new_node->type = get_token(new_node->data);  A voir */
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void add_back(t_list **head, char *data)
{
    t_list	*new_node = create_node(data);
	t_list	*temp;

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

void free_list(t_list **head)
{
	t_list *current;
	t_list *temp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		temp = current->next;
		w_free((void **)&(current->data));
		w_free((void **)&current);
		current = temp;
	}
	*head = NULL;
}


size_t count_cmd(t_list *head)
{
	size_t	c;
	t_list	*temp;

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
