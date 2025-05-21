/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/21 18:54:41 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*add_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	node = ast_new_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = AST_PIPE;
	node->data.ast_pipe.left = left;
	node->data.ast_pipe.right = right;
	return (node);
}


// '>'	fd = 1, O_WRONLY | O_CREATE | O_TRUNC	-> mode = 1 (redir output)(creating / overwriting)
// '>>'	fd = 1, O_WRONLY | O_CREATE				-> mode = 2 (redir output)(appending)
// '<'	fd = 0, O_RDONLY						-> mode = 3 (redir input)(reading)
// '<<'	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
t_ast	*add_redir_node(t_ast *left, char *filename, int mode)
{
	t_ast	*node;

	if (!left)
		return (NULL);
	node = ast_new_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = AST_REDIR;
	node->data.ast_redir.left = left;
	node->data.ast_redir.mode = mode;
	node->data.ast_redir.filename = ft_strdup(filename);
	if (!node->data.ast_redir.filename)
	{
		errno = ENOMEM;
		ft_puterror("add_redir_node", strerror(errno));
		return (NULL);
	}
	return (node);
}

t_ast	*add_exec_node(t_list **tok)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = AST_EXEC;
	node->data.ast_exec.argc = 0;
	w_malloc((void**)&node->data.ast_exec.argv, (sizeof(char**) * 10)); // 🗯️ Nombre d'args max à gérer ❔
	while (*tok && (*tok)->type == WORD)
	{
		node->data.ast_exec.argv[node->data.ast_exec.argc++]
			= fill_exec_node(*tok);
		if (!node->data.ast_exec.argv[node->data.ast_exec.argc - 1]) // 🗯️ -1❔
		{
			ft_free_char_array(node->data.ast_exec.argv,
				node->data.ast_exec.argc - 1); // 🗯️ -1❔
			return (NULL);
		}
		if (!tok || !(*tok)->next)
			break ;
		else
			get_next_token(tok);
	}
	node->data.ast_exec.argv[node->data.ast_exec.argc] = '\0';
	return (node);
}

t_ast	*ast_new_node(t_ast node)
{
	t_ast	*ptr;

	w_malloc((void **)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = node;
	return (ptr);
}
