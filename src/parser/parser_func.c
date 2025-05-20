/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/20 09:26:08 by emonacho         ###   ########.fr       */
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
	left = parse_exec(tok);					// on commence par parser le noeud le plus à droite
	while (*tok && (*tok)->type == PIPE)
	{
		get_next_token(tok);				// consomme '|'
		right = parse_exec(tok);			// parse la commande à gauche du pipe
		left = add_pipe_node(left, right);	// construit node: gauche = left, droite = right
		print_node(left); // 🖨️PRINT💥DEBUGING
	}
	return (left);
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
			left = add_redir_node(left, (*tok)->next->data, IN_REDIR);
		else if ((*tok)->type == OUT_REDIR)
			left = add_redir_node(left, (*tok)->next->data, OUT_REDIR);
		else if ((*tok)->type == APP_OUT_REDIR)
			left = add_redir_node(left, (*tok)->next->data, APP_OUT_REDIR);
		else if ((*tok)->type == HERE_DOC)
			left = add_redir_node(left, (*tok)->next->data, HERE_DOC);
		get_next_token(tok);
		get_next_token(tok);
		print_node(left); // 🖨️PRINT💥DEBUGING
	}
	return (left);
}

// parse_exec: REDIR {aaa REDIR}
t_ast	*parse_exec(t_list **tok)
{
	t_ast	*root_ptr;
	t_ast	*exec_node;

	fprintf(stderr, "parse_exec | current token: %s%s%s\n", Y, (*tok)->data, RST); // 🖨️PRINT💥DEBUGING
	if ((*tok) && (*tok)->type == WORD)
	{
		exec_node = add_exec_node(tok);
		print_node(exec_node); // 🖨️PRINT💥DEBUGING
	}
	root_ptr = exec_node;

	//if ((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))
	while((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))
	{
		//fprintf(stderr, "parse_exec | %s%s%s\n", Y, "if ((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))", RST);
		root_ptr = parse_redir(tok, root_ptr);
		print_node(root_ptr); // 🖨️PRINT💥DEBUGING
	}
	/*if ((*tok)->next && !((*tok)->type == WORD || (*tok)->type == PIPE))
	{
		fprintf(stderr, "parse_exec | %s%s%s\n", Y, "if ((*tok)->next)", RST);
		root_ptr = parse_exec(tok);
		fprintf(stderr, "parse_exec | %s%s%s\n", Y, "root_ptr pointing to: ", RST);
		print_node(root_ptr);
	}*/

	// BACKUP 💾
	/*if ((*tok)->next)
		root_ptr = parse_redir(tok, root_ptr);
	if ((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))
		root_ptr->data.ast_redir.left = parse_exec(tok);*/

	return (root_ptr);
}


// BACKUP 💾
/*t_ast	*parse_exec(t_list **tok)
{
	t_ast	*root_ptr;
	t_ast	*exec_node;

	exec_node = add_exec_node(tok);
	print_node(exec_node); // 🖨️PRINT💥DEBUGING
	root_ptr = exec_node;
	root_ptr = parse_redir(tok, root_ptr);
	if ((*tok) && !((*tok)->type == WORD || (*tok)->type == PIPE))
		root_ptr = parse_redir(tok, root_ptr);
	return (root_ptr);
}*/
