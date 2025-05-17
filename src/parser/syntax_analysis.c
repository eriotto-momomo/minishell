/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:33 by timmi             #+#    #+#             */
/*   Updated: 2025/05/17 15:18:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	quote_check(t_list *tok)
{
	if (tok->data[0] == '\'' || tok->data[0] == '\"')
	{
		if (tok->data[0] == '\'' && tok->data[ft_strlen(tok->data) - 1] != '\'')
			return (UNMATCHED_QUOTE);
		else if (tok->data[0] == '\"' && tok->data[ft_strlen(tok->data) - 1] != '\"')
			return (UNMATCHED_QUOTE);
	}
	return (0);
}

static int	syntax_checker(t_list *tok)
{
	if (tok->data[0] == '\"' || tok->data[0] == '\'')
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

int	syntax_analysis(t_list *current_tok)
{
	int		err;

	while (current_tok)
	{
		err = syntax_checker(current_tok);
		if (err)
		{
			print_error(err);
			return (1);
		}
		current_tok = current_tok->next;
	}
	return (0);
}
