/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/05/29 12:35:07 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	tokenize(t_list **head, char *cmd)
{
	char	*ptr;
	char	*el;

	if (!cmd || !*cmd)
		return (1);
	ptr = cmd;
	while (ptr)
	{
		while (ft_isspace(*ptr))
			ptr++;
		if (!*ptr)
			return (1);
		el = get_el(ptr);
		printf("el :%s\n", el);
		if (!el)
			return (0);
		ptr += ft_strlen(el);
		if (!add_back(head, el))
			return (0);
	}
	return (1);
}


void	lexer(t_shell *s)
{
	t_list	*token;

	token = NULL;
	s->head = token;
	rm_quote(s->line);
	if (!tokenize(&(s->head), s->line))
	{
		perror("Something went wrong");
		terminate_shell(s);
	}
	exit_check(s);
}
