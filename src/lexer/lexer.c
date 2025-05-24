/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/05/24 16:34:43 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_el(char *cmd)
{
	char *to_push;

	if (*cmd == '\'' || *cmd == '\"')
		to_push = get_quote(cmd);
	else if (is_sep(*cmd))
		to_push = get_sep(cmd);
	else
		to_push = get_word(cmd);
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

int tokenize(t_list **head, char *cmd)
{
	char	*el;
	char	*rest;
	size_t	len;

	if (!cmd || !*cmd)
		return (1);
	while (ft_isspace(*cmd))
		cmd++;
	el = get_el(cmd);
	if (!el)
		return (0);
	len = ft_strlen(el);
	rest = ft_strdup(cmd + len);
	if (!rest)
	{
		free(el);
		return (0);
	}
	if (!add_back(head, el))
	{
		free(el);
		free(rest);
		return (0);
	}
	free(el);
	return (tokenize(head, rest));
}


void	lexer(t_shell *s)
{
	t_list	*token;
	char	*to_tokenize;

	token = NULL;
	s->head = token;
	to_tokenize = s->line;
	if (tokenize(&(s->head), to_tokenize))
	{
		perror("Something went wrong");
		terminate_shell(s);
	}
	exit_check(s);
}
