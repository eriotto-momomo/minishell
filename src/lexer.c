/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/04/09 10:40:06 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return(0);
}

int	is_sep(char c)
{
	int i;
	
	i = 0;
	while (SEPARATORS[i])
	{
		if (c == SEPARATORS[i])
			return (1);
		i++;
	}
	return (0);
}

static char *push_sep(char sep)
{
	char *new_str;

	new_str = malloc(sizeof(char) * 2);
	if (!new_str)
		return (NULL);
	new_str[0] = sep;
	new_str[1] = '\0';
	return (new_str);
}

static char	*push_word(char **cmd)
{
	char	*new_str;
	int		i;

	i = 0;
	while (!(is_sep((*cmd)[i]) || is_space((*cmd)[i])))
		i++;
	new_str = malloc((sizeof(char) * i) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (**cmd && !(is_sep(**cmd) || is_space(**cmd)))
	{
		new_str[i++] = **cmd;
		(*cmd)++;
	}
	new_str[i] = '\0';
	return (new_str);
}

t_list *cmd_splicing(char *cmd)
{
	t_list	*head;

	if (!cmd)
		return (NULL);
	head = NULL;
	while (*cmd)
	{
		if (is_sep(*cmd))
		{ 
			add_back(&head, push_sep(*cmd));
			cmd++;
		}
		else
			add_back(&head, push_word(&cmd));
		while (is_space(*cmd))
			cmd++;
	}
	// Just to see linked list
	t_list *temp = head;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
	return(head);
}
