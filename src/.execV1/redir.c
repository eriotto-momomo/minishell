/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/30 20:54:32 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_input(t_shell *s, t_ast *current_node)
{
	//printf("redirect_input | current_node\n");
	//print_node(current_node);
	if (current_node->data.ast_redir.mode == IN_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_RDONLY);
	else if (current_node->data.ast_redir.mode == HERE_DOC)
		s->fd = open(s->heredoc_tmp, O_RDONLY);
	if (s->fd < 0)
		return (-1);
	if (close(s->fd) < 0)
		return (-1);
	printf("%sredirect_input | s->fd = %d%s\n", G, s->fd, RST);


	//🚩 MARCHE MAIS C'EST PAS UNE VRAIE REDIR ❔❔❔
	//if (current_node->data.ast_redir.mode == IN_REDIR
	//		&& current_node->data.ast_redir.left->tag == AST_EXEC)
	//	current_node->data.ast_redir.left->data.ast_exec.argv
	//	[current_node->data.ast_redir.left->data.ast_exec.argc] =
	//		ft_strdup(current_node->data.ast_redir.filename);
	//else if (current_node->data.ast_redir.mode == HERE_DOC
	//		&& current_node->data.ast_redir.left->tag == AST_EXEC)
	//	current_node->data.ast_redir.left->data.ast_exec.argv
	//	[current_node->data.ast_redir.left->data.ast_exec.argc] =
	//		ft_strdup(s->heredoc_tmp);
	//if (!current_node->data.ast_redir.left->data.ast_exec.argv
	//	[current_node->data.ast_redir.left->data.ast_exec.argc])
	//	return (-1);
	//return (0);
	//🚩 MARCHE MAIS C'EST PAS UNE VRAIE REDIR ❔❔❔

	return (s->fd);
}

int	redirect(t_shell *s, t_ast *current_node, int fd_in, int fd_out)
{
	printf("%sredirect |[1] fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	s->fd = -1;
	if (current_node->data.ast_redir.mode == HERE_DOC)
	{
		printf("redirect| %scurrent_node BEFORE handle_heredoc%s\n", Y, RST);
		print_node(current_node);
		s->fd = handle_heredoc(s, current_node, fd_in, fd_out);
		s->root_redir = NULL;
		printf("redirect| %scurrent_node AFTER handle_heredoc%s\n", Y, RST);
		print_node(current_node);
	}
	else if (current_node->data.ast_redir.mode == IN_REDIR)
		s->fd = redirect_input(s, current_node);
	else if (current_node->data.ast_redir.mode == OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (current_node->data.ast_redir.mode == APP_OUT_REDIR)
		s->fd = open(current_node->data.ast_redir.filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (s->fd < 0)
		return (-1);
	printf("%sredirect|[2] fd_in: %d | fd_out: %d%s\n", P, fd_in, fd_out, RST);
	return (s->fd);
}
// 🚩 Le FD des OUT_REDIR est a 'close' apres les redirections 🚩
