/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:33 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 23:08:36 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_match_quote(char *s, int i)
{
	char	quote;
	
	quote = s[i++];
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		return (i);
	return (0);
}

static int	quote_check(t_token *tok)
{
	int		start;

	start = 0;
	while (tok->data[start])
	{
		if (ft_isquote(tok->data[start]))
		{
			start = check_match_quote(tok->data, start);
			if (!start)
				return (UNMATCHED_QUOTE);
		}
		start++;
	}
	return (0);
}

static int	syntax_checker(t_token *tok)
{
	if (ft_strchr(tok->data, '\'') || ft_strchr(tok->data, '\"'))
		return (quote_check(tok));
	if (tok->type == OUT_REDIR || tok->type == IN_REDIR
		|| tok->type == HERE_DOC || tok->type == APP_OUT_REDIR)
	{
		if (!tok->next)
			return (UNEXPECTED_TOK);
	}
	if (tok->type == PIPE)
	{
		if (!tok->prev || !tok->next || tok->prev->type != WORD)
			return (UNEXPECTED_TOK);
		else if (tok->next->type == PIPE)
			return (UNEXPECTED_TOK);
	}
	return (0);
}

int	syntax_analysis(t_token *current_tok)
{
	int		err;

	while (current_tok)
	{
		err = syntax_checker(current_tok);
		if (err)
		{
			ft_putstr_fd("Syntax", err);
			return (1);
		}
		current_tok = current_tok->next;
	}
	return (0);
}
