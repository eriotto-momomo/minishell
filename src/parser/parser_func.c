/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/06 14:13:15 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// parse_pipe: EXEC [|PIPE]
t_ast	*parse_pipe(t_list **tok)
{
	t_ast	*right;
	t_ast	*left;

	if (!*tok || (*tok)->data == NULL)
		return (NULL);
	left = parse_exec(tok);				// on commence par parser le noeud le plus à droite
	if (!left)
		return (NULL);
	while (*tok && (*tok)->type == PIPE)
	{
		right = parse_exec(tok);			// parse la commande à gauche du pipe
		if (!right)
			return (NULL);
		left = add_pipe_node(left, right);	// construit node: gauche = left, droite = right
		if (!left)
			return (NULL);
		print_node(left); // 🖨️PRINT💥DEBUGING
	}
	return (left);
}

// parse_line: PIPE {&} [;LINE]
t_ast	*parse_line(t_list **tok)
{
	t_ast	*node;

	node = parse_pipe(tok);
	if (!node)
		return (NULL);
	return (node);
}

// parse_exec: REDIR {aaa REDIR}
t_ast	*parse_exec(t_list **tok)
{
	t_ast	*exec_node;

	if ((*tok) && (*tok)->type != PIPE)
	{
		exec_node = add_exec_node(tok);
		if (!exec_node)
			return (NULL);
		//print_node(exec_node); // 🖨️PRINT💥DEBUGING
		get_next_pipe(tok);
	}
	return (exec_node);
}

void	get_next_pipe(t_list **tok)
{
	while ((*tok) && (*tok)->type != PIPE)
	{
		if (!get_next_token(tok))
			break;
	}
}

int	get_next_token(t_list **tok)
{
	if (!(*tok) || !(*tok)->next)
		return (0);
	*tok = (*tok)->next;
	return (1);
}
