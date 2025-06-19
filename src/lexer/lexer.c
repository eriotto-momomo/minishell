/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 13:13:34 by timmi            ###   ########.fr       */
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
		printf("el : %s\n", el);
		if (!el)
			return (0);
		ptr += ft_strlen(el);
		if (!add_token_back(head, el))
			return (0);
	}
	return (1);
}

void	lexer(t_shell *s)
{
	t_token	*token;

	token = NULL;
	s->head = token;
	if (!tokenize(&(s->head), s->line))
	{
		perror("Something went wrong");
		terminate_shell(s, 0);
	}
	for (t_token *tmp = s->head; tmp; tmp = tmp->next)
		printf("tmp :%s\n", tmp->data);
	exit_check(s);
}
