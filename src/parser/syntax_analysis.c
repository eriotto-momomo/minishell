/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:33 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 21:35:16 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	else if (temp->type == OUT_REDIR || temp->type == IN_REDIR || temp->type == HERE_DOC || temp->type == APP_OUT_REDIR)
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
			if (!temp->next)
				printf("minishell: syntax error near unexpected token `newline'\n");
			printf("%sSyntax error n %d\n%s",R, err, RST);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
