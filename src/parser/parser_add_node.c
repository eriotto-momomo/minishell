/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/29 17:13:54 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_in_heredoc_list(t_shell *s, char *filename)
{
	s->heredoc_list = grow_array(s->heredoc_list, s->heredoc_count);
	printf("put_in_heredoc_list| filename: [%s%s%s]\n", G, filename, RST);
	printf("put_in_heredoc_list| s->heredoc_list[%d]: %s%s%s]\n", s->heredoc_count, Y, s->heredoc_list[s->heredoc_count], RST);
	if (!s->heredoc_list)
		return (1);
	s->heredoc_list[s->heredoc_count] = ft_strdup(filename);

	if (!s->heredoc_list[s->heredoc_count])
	{
		ft_free_char_array(s->heredoc_list, s->heredoc_count - 1);
		return (1);
	}
	s->heredoc_count++;
	return (0);
}

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
t_ast	*add_redir_node(t_shell *s, t_ast *left, char *filename, int mode)
{
	(void)s;
	t_ast	*node;

	if (!left)
		return (NULL);
	node = ast_new_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = AST_REDIR;
	node->data.ast_redir.left = left;
	node->data.ast_redir.mode = mode;
	if (mode == HERE_DOC)
	{
		if (put_in_heredoc_list(s, filename) != 0)
			return (NULL);
	}
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
	int		i;

	node = ast_new_node((t_ast){0});
	if (!node)
		return (NULL);
	node->tag = AST_EXEC;
	node->data.ast_exec.argc = count_args(*tok);
	node->data.ast_exec.argv = malloc(sizeof(char **) * (node->data.ast_exec.argc + 1)); //📍`+1` au cas ou il y'a un HEREDOC a gerer
	if (!node->data.ast_exec.argv)
			return (NULL);
	i = 0;
	while ((*tok && (*tok)->type == WORD) && i < node->data.ast_exec.argc)
	{
		node->data.ast_exec.argv[i] = fill_exec_node(*tok);
		if (!node->data.ast_exec.argv[i])
			return (ft_free_char_array(node->data.ast_exec.argv, i));
		if (!get_next_token(tok))
			break ;
		i++;
	}
	node->data.ast_exec.argv[node->data.ast_exec.argc] = '\0';
	return (node);
}

t_ast	*ast_new_node(t_ast node)
{
	t_ast	*ptr;

	//w_malloc((void **)&ptr, sizeof(t_ast));
	ptr = malloc(sizeof(t_ast));
	if (ptr)
		*ptr = node;
	return (ptr);
}
