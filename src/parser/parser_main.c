/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/15 16:15:27 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*build_ast(t_list **tok)
{
	t_ast	*ast;

	ast = parse_line(tok);
	return (ast);
}

void	parser(t_shell *s)
{
	t_list *temp;

	temp = s->head;
	if (!syntax_analysis(temp))
		terminate_shell(s);
	s->root_node = build_ast(&temp);
	//printf("%s============ ROOT NODE ============%s\n", Y, RST); // PRINT DEBUGGING 📠
	//print_node(s->root_node); // PRINT DEBUGGING 📠
	//printf("%s===================================%s\n", Y, RST); // PRINT DEBUGGING 📠
}

void print_preorder(t_ast *node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	if (node->tag == AST_PIPE)
		printf("|\n");
	else if (node->tag == AST_REDIR)
		printf(">\n");
	else if (node->tag == AST_EXEC)
		printf("%s\n", node->data.ast_exec.argv[0]);

	if (node->tag != AST_EXEC)
	{
		print_preorder(node->data.ast_pipe.left);
		print_preorder(node->data.ast_pipe.right);
	}
	else
		return;
}
