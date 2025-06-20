/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/20 15:28:50 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	to_sep(int in_quote, char c)
{
	if (!in_quote && ft_isspace(c))
		return (1);
	if (!in_quote && is_sep(c))
		return (1);
	return (0);
}

static size_t	get_tok_len(char *cmd)
{
    size_t	len;
    int		in_quote;
    char	quote_type;

	len = 0;
	in_quote = 0;
	quote_type = '\0';
    while (cmd[len])
    {
		if (!in_quote && ft_isquote(cmd[len]))
		{
			in_quote = 1;
			quote_type = cmd[len++];
		}
		else if (in_quote && cmd[len] == quote_type)
		{
			in_quote = 0;
			len++;
		}
		else if (to_sep(in_quote, cmd[len]) != 0)
			break;
		else
			len++;
	}
	return (len);
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

static char	*get_sep(char *cmd)
{
	char	*sep;

	if (!cmd)
		return (NULL);
	if ((cmd[0] == '<' && cmd[1] == '<') || (cmd[0] == '>' && cmd[1] == '>'))
	{
		sep = malloc(3);
		if (!sep)
			return (NULL);
		sep[0] = cmd[0];
		sep[1] = cmd[1];
		sep[2] = '\0';
	}
	else
	{
		sep = malloc(2);
		if (!sep)
			return (NULL);
		sep[0] = cmd[0];
		sep[1] = '\0';
	}
	return (sep);
}

static char	*get_word(char *cmd)
{
	size_t	len;
	char	*word;
	size_t	i;

	if (!cmd)
		return (NULL);
	len = get_tok_len(cmd);
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = cmd[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*get_el(char *cmd)
{
	if (is_sep(*cmd))
		return (get_sep(cmd));
	return (get_word(cmd));
}
