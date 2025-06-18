/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:27 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 11:05:18 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *create_token(char *data)
{
	t_token	*new_node;

	new_node = (t_token*)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->type = get_token_id(data);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	add_token_back(t_token **head, char *data)
{
    t_token	*new_node;
	t_token	*temp;

	// if (ft_strncmp(data, "", 1) == 0)
	// 	return (1);
	new_node = create_token(data);
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

void free_token_list(t_token **head)
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
