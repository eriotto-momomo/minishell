/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:33 by timmi             #+#    #+#             */
/*   Updated: 2025/06/21 19:16:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_limits(t_shell *s, t_token *tok)
{
	if (tok->type == WORD)
		s->tok_word++;
	if (tok->type == PIPE)
		s->tok_pipe++;
	else if (tok->type == OUT_REDIR || tok->type == APP_OUT_REDIR
		|| tok->type == IN_REDIR || tok->type == HERE_DOC)
		s->tok_rdir++;
	if (s->tok_rdir > 1024 || s->tok_pipe > 256 || s->tok_word > ARG_MAX)
	{
		if (s->tok_rdir > 1024 )
			errno = EMFILE;
		if (s->tok_pipe > 256)
			errno = EAGAIN;
		if (s->tok_word > ARG_MAX)
			errno = E2BIG;
		return (1);
	}
	return (0);
}

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
				return (2);
		}
		start++;
	}
	return (0);
}

static int	syntax_checker(t_shell *s, t_token *tok)
{
	if (check_limits(s, tok) != 0)
		return (4);
	if (ft_strchr(tok->data, '\'') || ft_strchr(tok->data, '\"'))
		return (quote_check(tok));
	if (tok->type == OUT_REDIR || tok->type == IN_REDIR
		|| tok->type == HERE_DOC || tok->type == APP_OUT_REDIR)
	{
		if (!tok->next)
			return (3);
	}
	if (tok->type == PIPE)
	{
		if (!tok->prev || !tok->next || tok->prev->type != WORD)
			return (3);
		else if (tok->next->type == PIPE)
			return (3);
	}
	return (0);
}

int	syntax_analysis(t_shell *s, t_token *current_tok)
{
	int err;

	while (current_tok)
	{
		err = syntax_checker(s, current_tok);
		if (err)
		{
			s->numerr = err;
			if (err == 2)
				ft_puterror("syntax_analysis", "Unmatched quote !\n");
			else if (err == 3)
				ft_putstr_fd("Unexpected token found !\n", STDERR_FILENO);
			else if (err == 4)
				print_error(&s->numerr, errno, "syntax_analysis");
			return (1);
		}
		current_tok = current_tok->next;
	}
	return (0);
}
