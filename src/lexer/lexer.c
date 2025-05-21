/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/05/21 17:01:12 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_el(char *cmd, int i)
{
	char *to_push;

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

	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APP_OUT_REDIR);
		return (OUT_REDIR);
	}
	if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HERE_DOC);
		return (IN_REDIR);
	}
	if (token[0] == '|')
		return (PIPE);
	return (WORD);
}

t_list *tokenize(char *cmd)
{
	int i;
	char *el;
	t_list *head;

	i = 0;
	head = NULL;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		el = get_el(cmd, i);
		if (!el)
		{
			free_list(&head);
			return (NULL);
		}
		if (add_back(&head, el) == 1)
		{
			free_list(&head);
			return (NULL);
		}
		i += ft_strlen(el);
	}
	return (head);
}

void	lexer(t_shell *s)
{
	s->head = tokenize(s->line);
	if (!s->head)
		terminate_shell(s, errno);
	exit_check(s);
}
