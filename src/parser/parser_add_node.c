/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/06 18:09:04 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_command(t_ast **node, t_list **tok)
{
	(*node)->tag = EXEC_NODE;
	(*node)->data.exec.argc = count_tokens(&(*tok), WORD);
	(*node)->data.exec.argv = malloc(sizeof(char **) * ((*node)->data.exec.argc)); //📍`+1` au cas ou il y'a un HEREDOC a gerer
	if (!(*node)->data.exec.argv)
		return (1);
	if (copy_tokens(&(*tok), WORD, (*node)->data.exec.argc,
		(*node)->data.exec.argv) != 0)
		return (1);
	//printf("%sadd_command | BUG!%s\n", R, RST);
	return (0);
}

int	add_heredoc(t_ast **node, t_list **tok)
{
	(*node)->data.exec.heredoc_count = count_tokens(&(*tok), HERE_DOC);
	if ((*node)->data.exec.heredoc_count == 0)
		return (0);
	(*node)->data.exec.heredoc_list =
		malloc(sizeof(char **) * (*node)->data.exec.heredoc_count);
	if (!(*node)->data.exec.heredoc_list)
		return (1);
	if (copy_tokens(&(*tok), HERE_DOC, (*node)->data.exec.heredoc_count,
		(*node)->data.exec.heredoc_list) != 0)
		return (1);
	//printf("%sadd_heredoc | BUG!%s\n", R, RST);
	return (0);
}

int	add_redir(t_ast **node, t_list **tok)
{
	t_list	*tmp;

	(*node)->data.exec.fd_in = 0;
	(*node)->data.exec.fd_out = 1;
	tmp = *tok;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUT_REDIR || tmp->type == APP_OUT_REDIR)
			(*node)->data.exec.fd_out = redir_out(tmp->type, tmp->next->data, (*node)->data.exec.fd_out);
		else if (tmp->type == IN_REDIR)
			(*node)->data.exec.fd_in = redir_in(tmp->next->data, (*node)->data.exec.fd_in);
		if ((*node)->data.exec.fd_out < 0 || (*node)->data.exec.fd_in < 0)
			return (1);
		if (!get_next_token(&tmp))
			break;
	}
	return (0);
}

t_ast	*add_exec_node(t_list **tok)
{
	t_ast	*node;

	node = new_ast_node((t_ast){0});
	if (!node)
		return (NULL);
	if (add_command(&node, tok) != 0)
		return (NULL);
	if (add_heredoc(&node, tok) != 0)
	{
		ft_free_char_array(node->data.exec.argv, node->data.exec.argc);
		return (NULL);
	}
	if (add_redir(&node, tok) != 0)
	{
		ft_free_char_array(node->data.exec.argv, node->data.exec.argc);
		ft_free_char_array(node->data.exec.heredoc_list,
			node->data.exec.heredoc_count);
		return (NULL);
	}
	return (node);
}

t_ast	*add_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	node = new_ast_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = PIPE_NODE;
	node->data.pipe.left = left;
	node->data.pipe.right = right;
	return (node);
}
