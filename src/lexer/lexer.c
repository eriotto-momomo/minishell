/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 09:52:23 by timmi            ###   ########.fr       */
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
		if (!el)
			return (0);
		ptr += ft_strlen(el);
		if (!add_back(head, el))
			return (0);
	}
	return (1);
}

// static int	count_pipe(t_list *head)
// {
// 	int	c_pipe;

// 	c_pipe = 0;
// 	while (head)
// 	{
// 		if (head->type == PIPE)
// 			c_pipe++;
// 		head = head->next;
// 	}
// 	return (c_pipe);
// }

void	lexer(t_shell *s)
{
	t_list	*token;

	token = NULL;
	s->head = token;
	if (!tokenize(&(s->head), s->line))
	{
		perror("Something went wrong");
		terminate_shell(s, 0);
	}
	// s->pipe_count = count_pipe(s->head);
	exit_check(s);
}
