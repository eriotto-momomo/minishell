/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:37:22 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/05 16:05:42 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_pipe_node(t_ast *node)
{
	if (node->data.pipe.left)
	{
		if (node->data.pipe.left->tag == EXEC_NODE)
			free_exec_node(node->data.pipe.left);
		else if (node->data.pipe.left->tag == PIPE_NODE)
			free_pipe_node(node->data.pipe.left);
	}
	if (node->data.pipe.right)
	{
		if (node->data.pipe.right->tag == EXEC_NODE)
			free_exec_node(node->data.pipe.right);
		else if (node->data.pipe.right->tag == PIPE_NODE)
			free_pipe_node(node->data.pipe.right);
	}
	w_free((void **)&node);
	printf("%s🔶FREE PIPE_NODE.|%s %sFREED!%s\n", Y, RST, G, RST); // PRINT DEBUGGING 📠
}

void	free_exec_node(t_ast *node)
{
	int	i;

	if (node->data.exec.argv && node->data.exec.argv[0]
			&& node->data.exec.argc > 0)
	{
		i = 0;
		printf("%s🔵FREE EXEC_NODE.|%s %sFREED!%s", B, RST, G, RST); // PRINT DEBUGGING 📠
		// 🚨TEST🚨 **argv is allocated with more slots than usually required (10)
		while (node->data.exec.argv[i])
		{
			printf(" %sargv[%d]%s[%s]", B, i, RST, node->data.exec.argv[i]); // PRINT DEBUGGING 📠
			//if (ft_strncmp(node->data.exec.argv[i], "./tmp/heredoc_tmp.txt",
			//		ft_strlen(node->data.exec.argv[i])))
			//{
			//	w_free((void **)&s->heredoc_tmp);
			//	unlink("./tmp/heredoc_tmp.txt");
			//}
			w_free((void **)&node->data.exec.argv[i]);
			i++;
		}
		printf("\n"); // PRINT DEBUGGING 📠

		// BACKUP 💾
		//while (i < node->data.exec.argc)
		//{
		//	//printf(" %sargv[%d]%s[%s]", B, i, RST, node->data.exec.argv[i]); // PRINT DEBUGGING 📠
		//	w_free((void **)&node->data.exec.argv[i]);
		//	i++;
		//}

		node->data.exec.argc = 0;
		w_free((void **)&node->data.exec.argv);
		w_free((void **)&node);
	}
}

void	free_ast(t_ast **node)
{
	if (!node)
		return ;
	if (node && (*node)->tag == PIPE_NODE)
		free_pipe_node(*node);
	else if (node && (*node)->tag == EXEC_NODE)
		free_exec_node(*node);
	*node = NULL;
	printf("%s🔥AST FREED🔥%s\n", G, RST); // PRINT DEBUGGING 📠
}
