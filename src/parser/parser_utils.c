/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/22 18:10:52 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast	*ast_new_node(t_ast cmd)
{
	t_ast	*ptr;

	//ptr = malloc(sizeof(t_ast));
	w_malloc((void**)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = cmd;
	return (ptr);
}

void	consume_token(t_list **head)
{
	if ((*head)->data)
	{
		free((*head)->data);
		(*head)->data = NULL;
		//printf("consume_token | %sfree((*head)->data)%s\n", C, RST);	// 💥DEBUGING
	}
	if ((*head)->next)
	{
		*head = (*head)->next; // Différence entr ça et: `head = &(*head)->next;` ?
		//printf("&& %shead = (*head)->next%s\n", C, RST);				// 💥DEBUGING
	}
}

void	print_exec_args(char **node)
{
	int	i;

	i = 0;
	while (node[i] && node[i][0])
	{
		printf("printf_exec_args | ");
		printf("[%s%s%s] ", C, node[i], RST);			// 💥DEBUGING
		printf("\n");
		i++;
	}
}

void	print_ast(t_ast *ast)
{
	t_ast *left = ast->data.ast_pipe.left;
	t_ast *right = ast->data.ast_pipe.right;
	if (ast->tag == AST_PIPE)
	{
		if (left->tag == AST_EXEC)
		{
			printf("LEFT  BRANCH:");
			for (int i = 0; i < left->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, left->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (left->tag == AST_PIPE)
			printf("LEFT  BRANCH: [%sAST_PIPE%s node]\n", P, RST);
		if (right->tag == AST_EXEC)
		{
			printf("RIGHT BRANCH:");
			for (int i = 0; i < right->data.ast_exec.argc; i++)
				printf(" [%s%s%s]", C, right->data.ast_exec.argv[i], RST);
			printf("\n");
		}
		else if (right->tag == AST_PIPE)
			printf("RIGHT BRANCH: [%sAST_PIPE%s node]\n", P, RST);
		else
			printf("[EMPTY BRANCH]\n");
	}
	/*else if (ast->tag == AST_BLOCK)
	{
	}
	else if (ast->tag == AST_REDIR)
	{
	}*/
}
