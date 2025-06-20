/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/06/20 18:03:40 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenize(t_token **head, char *cmd)
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
		if (!el)
			return (0);
		ptr += ft_strlen(el);
		if (!add_token_back(head, el))
			return (0);
	}
	return (1);
}

int	lexer(t_shell *s)
{
	t_token	*token;

	token = NULL;
	s->head = token;
	if (!tokenize(&(s->head), s->line))
		return (print_error(&s->numerr, ENOMEM, "tokenize"));
	for (t_token *tmp = s->head; tmp; tmp = tmp->next)
		printf("tmp :%s\n", tmp->data);
	return (0);
}
