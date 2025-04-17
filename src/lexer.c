/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/04/17 13:33:51 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_el(char *cmd, int i)
{
	char	*to_push;

	if (cmd[i] == '\'' || cmd[i] == '\"')
		to_push = get_quote(cmd, i);
	else if (is_sep(cmd[i]))
		to_push = get_sep(cmd, i);
	else
		to_push = get_word(cmd, i);
	return (to_push);
}

int	get_token_id(char *token)
{
	if (token[0] == '>' || token[0] == '<')
		return (REDIR);
	if (token[0] == '|')
		return (PIPE);
	return (WORD);
}

t_list	*tokenize(char *cmd)
{
	int		i;
	char	*el;
	t_list	*head;

	if (!cmd)
		return (NULL);
	i = 0;
	head = NULL;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		el = get_el(cmd, i);
		if (!el)
		{
			free_list(head);
			return (NULL);
		}
		add_back(&head, el);
		i += ft_strlen(el);
	}
	return (head);
}
