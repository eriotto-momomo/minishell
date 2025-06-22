/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 13:26:11 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*build_ast(t_token **tok)
{
	t_ast	*ast;

	ast = parse_line(tok);
	if (!ast)
		return (NULL);
	return (ast);
}

int	parser(t_shell *s)
{
	t_token *tmp;

	tmp = s->head;
	if (syntax_analysis(s, tmp) != 0)
		return (1);
	printf("%sparser | s->tok_pipe: %d | s->tok_rdir: %d | s->tok_word: %d%s\n", C, s->tok_pipe, s->tok_rdir, s->tok_word, RST);
	s->heredoc_list = NULL;
	s->heredoc_count = 1;
	s->root_node = build_ast(&tmp);
	if (!s->root_node)
	{
		if (errno != EBADF)
			errno = ENOMEM;
		return (print_error(&s->numerr, errno, "parser"));
	}
	s->current_node = s->root_node;
	free_token_list(&(s->head));
	return (0);
}

