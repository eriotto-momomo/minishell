/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 14:12:18 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int syntax_checker(t_list *token)
{
	int err;
	t_list *temp;

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

int syntax_analysis(t_list *token)
{
	t_list *temp;
	int err;

	temp = token;
	while (temp)
	{
		err = syntax_checker(temp);
		if (err)
		{
			printf("%sSyntax error n %d\n%s", R, err, RST);
			return (0);
		}
		temp = temp->next;
	}
	printf("Syntax Analysis passed !\n");
	return (1);
}

// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast	*build_ast(t_list **head)
{
	t_ast *ast;

	ast = parse_line(head);
	return (ast);
}

t_ast *parser(t_list *head)
{
	if (!syntax_analysis(head))
		return (NULL);
	return (build_ast(&head));
}