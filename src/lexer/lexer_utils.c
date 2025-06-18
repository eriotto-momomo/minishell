/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 10:47:02 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	get_tok_len(char *cmd)
{
	size_t	len;
	int		in_quote;
	char	quote_type;

	len = 0;
	in_quote = 0;
	while (cmd[len] && !is_sep(cmd[len]) && !ft_isspace(cmd[len]))
	{
		if (ft_isquote(cmd[len]))
		{
			in_quote = !in_quote;
			quote_type = cmd[len++];
		}
		if (in_quote)
			while (cmd[len] && cmd[len] != quote_type)
				len++;
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
