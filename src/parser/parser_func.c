/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/30 10:37:11 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// parse_pipe: EXEC [|PIPE]
t_ast	*parse_pipe(t_list **head)
{
	t_ast *cmd;

	cmd = parse_exec(head);
	// print_node(cmd);	// 🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING
	if ((*head)->type == PIPE)
	{
		consume_token(head);
		cmd = pipe_cmd(cmd, parse_pipe(head));
		// print_node(cmd);	// 🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING
	}
	return (cmd);
}

// parse_line: PIPE {&} [;LINE]
t_ast	*parse_line(t_list **head)
{
	t_ast *cmd;

	cmd = parse_pipe(head);

	// 🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING
	// printf("%sparse_line.%s| %sPARSING FINISHED! root_node to return%s:\n", R, RST, P, RST);	// 🖨️PRINT💥DEBUGING
	// print_node(cmd);	// 🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING🖨️PRINT💥DEBUGING

	return (cmd);
}

// parse_redir: {< file}, {> file} ou {>> file}
t_ast	*parse_redir(t_list **head, t_ast *left)
{
	if ((*head)->type != IN_REDIR && (*head)->type != OUT_REDIR
		&& (*head)->type != APP_OUT_REDIR && (*head)->type != HERE_DOC)
		return (left);
	if ((*head)->type == IN_REDIR)
		left = redir_cmd(left, (*head)->next->data, 1);
	else if ((*head)->type == OUT_REDIR)
		left = redir_cmd(left, (*head)->next->data, 2);
	else if ((*head)->type == APP_OUT_REDIR)
		left = redir_cmd(left, (*head)->next->data, 3);
	else if ((*head)->type == HERE_DOC)
		left = redir_cmd(left, (*head)->next->data, 4);
	consume_token(head);
	return (left);
}


// parse_exec: REDIR {aaa REDIR}
/*
*	`exec_node = exec_cmd(NULL);`: alloue un 'exec_node' (blank)	- ⚠️MALLOC ICI⚠️
*	`root_ptr = exec_node;`: pointe sur `exec_node`
* 	`root_ptr = parse_redir(head, root_ptr);`: redirige output de `exec_node` si `redir`
*/
t_ast	*parse_exec(t_list **head)
{
	t_ast	*root_ptr;
	t_ast	*exec_node;
	int		argc;

	exec_node = exec_cmd();
	root_ptr = exec_node;
	root_ptr = parse_redir(head, root_ptr);
	argc = 0;
	fill_exec_node(head, exec_node, &argc);
	if ((*head)->data && ((*head)->type == IN_REDIR || (*head)->type == OUT_REDIR
		|| (*head)->type == APP_OUT_REDIR || (*head)->type == HERE_DOC))
		root_ptr = parse_redir(head, root_ptr);
	exec_node->data.ast_exec.argc = argc;
	exec_node->data.ast_exec.argv[argc] = '\0';
	return (root_ptr);
}
