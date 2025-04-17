/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:04:12 by timmi             #+#    #+#             */
/*   Updated: 2025/04/17 17:14:54 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

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