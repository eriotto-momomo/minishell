/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/25 22:34:56 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*pipe_cmd(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
	{
		printf("%spipe_cmd...%s| %sNew node AST_PIPE creation failed%s!\n", Y, RST, R, RST);	// 💥DEBUGING
		return (NULL);
	}
	//if(node)
	//	printf("%spipe_cmd...%s| %sNew node AST_PIPE%s created!\n", Y, RST, G, RST);			// 💥DEBUGING
	node->tag = AST_PIPE;
	node->data.ast_pipe.left = left;
	node->data.ast_pipe.right = right;
	return (node);
}

// '<':		fd = 0, O_RDONLY						-> mode = 1 (redir input)(reading)
// '>':		fd = 1, O_WRONLY | O_CREATE | O_TRUNC	-> mode = 2 (redir output)(creating / overwriting)
// '>>':	fd = 1, O_WRONLY | O_CREATE				-> mode = 3 (redir output)(appending)
// '<<':	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
t_ast	*redir_cmd(t_ast *left, char *filename, int mode)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
	{
		printf("%sredir_cmd..%s| %sNew node AST_REDIR creation failed!%s\n", Y, RST, R, RST);	// 💥DEBUGING
		return (NULL);
	}
	//if(node)
	//	printf("%sredir_cmd..%s| %sNew node AST_REDIR%s created!\n", Y, RST, G, RST);			// 💥DEBUGING
	node->tag = AST_REDIR;
	node->data.ast_redir.left = left;
	node->data.ast_redir.mode = mode;
	node->data.ast_redir.filename = ft_strdup(filename);
	if (!node->data.ast_redir.filename)
	{
		errno = ENOMEM;
		ft_puterror("redir_cmd", strerror(errno));
		exit(1); // // 🗯️ Ou on "catch" errno dans le main pour quit clean ❔
	}
	return (node);
}

t_ast	*exec_cmd(void)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
	{
		printf("%sexec_cmd...%s| %sNew node AST_EXEC creation failed!%s\n", Y, RST, R, RST);	// 💥DEBUGING
		return (NULL);
	}
	//if(node)
	//	printf("%sexec_cmd...%s| %sNew node AST_EXEC%s created!\n", Y, RST, G, RST);			// 💥DEBUGING
	node->tag = AST_EXEC;
	node->data.ast_exec.argc = 0;
	w_malloc((void**)&node->data.ast_exec.argv, (sizeof(char**) * 10)); // 🗯️ Nombre d'args max à gérer ❔
	//node->data.ast_exec.argv = malloc(sizeof(char **) * 10);
	return (node);
}

t_ast	*ast_new_node(t_ast cmd)
{
	t_ast	*ptr;

	w_malloc((void **)&ptr, sizeof(t_ast));
	if (ptr)
		*ptr = cmd;
	return (ptr);
}
