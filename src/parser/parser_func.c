/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/02 15:15:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// parse_pipe: EXEC [|PIPE]
t_ast	*parse_pipe(t_list **tok)
{
	t_ast	*node;

	if ((*tok)->data == NULL)
		return (NULL);
	node = parse_exec(tok);
	if ((*tok) && (*tok)->type == PIPE)
	{
		get_next_token((tok));
		node = add_pipe_node(node, parse_pipe(tok));
		//print_node(node); // PRINT DEBUGGING 📠
	}
	return (node);
}

// parse_line: PIPE {&} [;LINE]
t_ast	*parse_line(t_list **tok)
{
	t_ast	*node;

	node = parse_pipe(tok);
	return (node);
}

// parse_redir: {< file}, {> file} ou {>> file}
t_ast	*parse_redir(t_list **tok, t_ast *left)
{
	if ((*tok))
	{
		if ((*tok)->type != IN_REDIR && (*tok)->type != OUT_REDIR
			&& (*tok)->type != APP_OUT_REDIR && (*tok)->type != HERE_DOC)
			return (left);
		if ((*tok)->type == IN_REDIR)
			left = add_redir_node(left, (*tok)->next->data, 1);
		else if ((*tok)->type == OUT_REDIR)
			left = add_redir_node(left, (*tok)->next->data, 2);
		else if ((*tok)->type == APP_OUT_REDIR)
			left = add_redir_node(left, (*tok)->next->data, 3);
		else if ((*tok)->type == HERE_DOC)
			left = add_redir_node(left, (*tok)->next->data, 4);
	}
	get_next_token(tok);
	get_next_token(tok);
	return (left);
}

// parse_exec: REDIR {aaa REDIR}
t_ast	*parse_exec(t_list **tok)
{
	t_ast	*root_ptr;
	t_ast	*exec_node;

	exec_node = add_exec_node(tok);
	//print_node(exec_node); // PRINT DEBUGGING 📠
	root_ptr = exec_node;
	root_ptr = parse_redir(tok, root_ptr);
	if ((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))
		root_ptr = parse_redir(tok, root_ptr);
	//print_node(root_ptr); // PRINT DEBUGGING 📠
	return (root_ptr);
}
