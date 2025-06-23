/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:35:20 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 10:41:48 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 🖨️PRINT💥DEBUGING
void	print_node(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;
	int i = 0;

	fprintf(stderr, "%s====================================%s\n", G, RST);
	if (ast->tag == EXEC_NODE)
	{
		fprintf(stderr, "%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		fprintf(stderr, "%sprint_node%s| argc: %d\n", B, RST, ast->data.s_exec.ac);
		fprintf(stderr, "%sprint_node%s| args:", B, RST);
		i = 0;
		while (i < ast->data.s_exec.ac)
		{
			fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.av[i], RST);
			i++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%sprint_node%s| fd_in:  %d\n", B, RST, ast->data.s_exec.fd_in);
		fprintf(stderr, "%sprint_node%s| fd_out: %d\n", B, RST, ast->data.s_exec.fd_out);
		if (ast->data.s_exec.heredoc_count == 0)
			fprintf(stderr, "%sprint_node%s| %sNo heredoc to handle!%s\n", B, RST, R, RST);
		else if (ast->data.s_exec.heredoc_count > 0)
		{
			fprintf(stderr, "%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.s_exec.heredoc_count)
			{
				fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.heredoc_list[i], RST);
				i++;
			}
			fprintf(stderr, "\n");
		}
	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.s_pipe.left;
		right = ast->data.s_pipe.right;
		fprintf(stderr, "%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		if (left->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| L. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		fprintf(stderr, "%s------------------------------------%s\n", G, RST);
		if (right->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| R. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
	}
	fprintf(stderr, "%s====================================%s\n", G, RST);

}
