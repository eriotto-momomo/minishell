/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:23:15 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/19 19:12:43 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_ast	*parse_block(t_list *head);
// t_ast	*parse_pipe(t_list *head);
// t_ast	*parse_line(t_list *head);
// t_ast	*parse_redir(t_list *head);
// t_ast	*parse_exec(t_list *head);

/*
t_ast	*parse_pipe(t_list *head)
{
	t_ast *ptr; // ???

	ptr = parse_exec(head);
	if (head->data == '|') // ???
		ptr = pipe_cmd(ptr, parse_pipe(head));
	return (ptr);
}
*/

/*
t_ast	*parse_redir(t_list *head)
{
	t_ast *ptr; // ???

	ptr = parse_exec(head); // ???
	if (head->data == '<') // ???
		ptr = redir_cmd(ptr, head->next->data, O_RDONLY, 0); // ???
	if (head->data == '>') // ???
		ptr = redir_cmd(ptr, head->next->data, O_WRONLY | O_CREATE | O_TRUNC, 1); // ???
	if (head->data == '>>') // ???
		ptr = redir_cmd(ptr, head->next->data, O_WRONLY | O_CREATE, 1); // ???
	return (ptr);
}
*/
