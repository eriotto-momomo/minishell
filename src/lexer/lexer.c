/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:53:56 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 09:33:45 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin(t_list *head)
{
	if (!head->prev || head->prev->type == PIPE)
	{
		if (ft_strncmp((*head).data, CD, ft_strlen(CD)) == 0)
			return (1);
		if (ft_strncmp((*head).data, ECHO, ft_strlen(ECHO)) == 0)
			return (1);
		if (ft_strncmp((*head).data, PWD, ft_strlen(PWD)) == 0)
			return (1);
		if (ft_strncmp((*head).data, ENV, ft_strlen(ENV)) == 0)
			return (1);
		if (ft_strncmp((*head).data, UNSET, ft_strlen(UNSET)) == 0)
			return (1);
		if (ft_strncmp((*head).data, EXPORT, ft_strlen(EXPORT)) == 0)
			return (1);
		return (0);
	}
	return (1);
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

static int	count_external(t_list *head)
{
	int	c;

	c = 0;
	while (head)
	{
		if (!is_builtin(head))
			c++;
		head = head->next;
	}
	return (c);
}

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
	s->ext_cmd_count = count_external(s->head);
	exit_check(s);
}
