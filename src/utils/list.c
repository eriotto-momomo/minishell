/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:27 by timmi             #+#    #+#             */
/*   Updated: 2025/04/24 13:59:37 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *create_node(char *data)
{
	t_list *newNode;

	newNode = (t_list *)malloc(sizeof(t_list));
	if (!newNode)
		return (NULL);
	newNode->data = data;
	newNode->type = get_token_id(data);
	/* newNode->type = get_token(newNode->data);  A voir */
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void add_front(t_list **head, char *data)
{
	t_list *newNode;

	newNode = create_node(data);
	if (!head)
	{
		*head = newNode;
		return;
	}
	newNode->next = *head;
	*head = newNode;
}

void add_back(t_list **head, char *data)
{
	t_list *newNode = create_node(data);
	t_list *temp;

	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newNode;
}

void free_list(t_list *head)
{
	t_list *temp;
	while (head)
	{
		temp = head->next;
		w_free(((void **)&(head->data)));
		w_free((void **)&head);
		head = temp;
	}
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
