/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/04/17 16:50:27 by timmi            ###   ########.fr       */
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

static int syntax_checker(t_list *token)
{
	int		err;
	t_list	*temp;

	err = 0;
	temp = token;
	if (temp->type == PIPE)
	{
		if (!temp->prev || !temp->next || temp->prev->type != WORD)
			err = 1; // minishell: syntax error near unexpected token `|\n
		else if (temp->next->type == PIPE)
			err = 2; // minishell: Does not handle `||\n
	}
	if (temp->type == OUT_REDIR || temp->type == IN_REDIR || temp->type == HERE_DOC)
	{
		if (!temp->next)
			err = 3; // minishell: syntax error near unexpected token `newline'\n
	}
	return (err);
}	

int	syntax_analysis(t_list *token)
{
	t_list	*temp;
	int		err;
	
	temp = token;
	while (temp)
	{
		err = syntax_checker(temp);
		if (err)
		{
			printf("%sSyntax error n %d\n%s",R, err, RST);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
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
