/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:33 by timmi             #+#    #+#             */
/*   Updated: 2025/05/15 15:53:54 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	quote_check(t_list *tok)
{
	int		err;

	err = 0;
	if (tok->data[0] == "\'" || tok->data[0] == '\"')
	{
		if (tok->data[0] == '\'' && tok->data[ft_strlen(tok->data)] != '\'')
			err = UNMATCHED_QUOTE;
		else if (tok->data[0] == '\"' && tok->data[ft_strlen(tok->data)] != '\"')
			err = UNMATCHED_QUOTE;
	}
	return (err);
}

static int	pipe_check(t_list *tok)
{
	int	err;
	
	err = 0;
	if (tok->type == PIPE)
	{
		if (!tok->prev || !tok->next || tok->prev->type != WORD)
			err = UNEXPECTED_TOK;
		else if (tok->next->type == PIPE)
			err = 2; // minishell: Does not handle `||\n
	}
	return (err);
}

static int	redir_check(t_list *tok)
{
	int	err;
	
	err = 0;
	if (tok->type == OUT_REDIR || tok->type == IN_REDIR
		|| tok->type == HERE_DOC || tok->type == APP_OUT_REDIR)
	{
		if (!tok->next)
			err = UNEXPECTED_TOK;
	}
	return (err);
}

static int	syntax_checker(t_list *tok, int *err)
{
	
}

int	syntax_analysis(t_shell *s)
{
	t_list	*current_tok;
	int		err;

	current_tok = s->head;
	while (current_tok)
	{
		syntax_checker(current_tok, &(s->err));
		if (s->err)
			return (0);
		current_tok = current_tok->next;
	}
	return (1);
}
