/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/20 22:07:43 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// `CONSTRUCTORS FUNCTIONS` pour créer les noeuds de l'AST
// ⚠️👷‍♂️ Travail en cours, fonctions probablement à modifier

t_ast	*block_cmd(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;

	// ... - TO DO👷‍♂️
	return (0);
}

t_ast	*pipe_cmd(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
	{
		printf("%spipe_cmd%s | New node %sAST_PIPE creation failed%s!\n", Y, RST, R, RST);	// 💥DEBUGING
		return (NULL);
	}
	if(node)
		printf("%spipe_cmd%s | New node %sAST_PIPE created%s!\n", Y, RST, G, RST);			// 💥DEBUGING
	node->tag = AST_PIPE;
	node->data.ast_pipe.left = left;
	node->data.ast_pipe.right = right;
	return (node);
}

t_ast	*line_cmd(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;

	// ... - TO DO👷‍♂️
	return (0);
}

/* `t_ast	*redir_cmd(t_ast *cmd, char *file_name, int oflag, int fd);`
* t_ast *cmd: pointeur sur le `sub-tree`
* char *file_name: pointeur sur le nom du fichier dans lequel rediriger
* int mode: mode de lecture (`O_RDONLY | O_WRONLY | O_CREATE | O_TRUNC`)
* int fd: 0 si < | <<, 1 si > | >> */
// '<':		fd = 0, O_RDONLY						-> mode = 1 (reading)
// '>':		fd = 1, O_WRONLY | O_CREATE | O_TRUNC	-> mode = 2 (creating / overwriting)
// '>>':	fd = 1, O_WRONLY | O_CREATE				-> mode = 3 (appending)
t_ast	*redir_cmd(t_ast *cmd, char *file_name, int mode, int fd)
{
	(void)cmd;
	(void)file_name;
	(void)mode;
	(void)fd;

	// ... - TO DO👷‍♂️
	return (0);
}

t_ast	*exec_cmd(void)
{
	t_ast	*node;

	node = ast_new_node((t_ast){0});
	if (!node)
	{
		printf("%sexec_cmd%s | %sNew node AST_EXEC creation failed!%s\n", Y, RST, R, RST);	// 💥DEBUGING
		return (NULL);
	}
	if(node)
		printf("%sexec_cmd%s | New node %sAST_EXEC created%s!\n", Y, RST, G, RST);			// 💥DEBUGING
	node->tag = AST_EXEC;
	node->data.ast_exec.argc = 0;
	w_malloc((void**)&node->data.ast_exec.argv, (sizeof(char**) * 10)); // À voir le nombre d'args max à gérer - ⚠️MALLOC ICI⚠️
	//node->data.ast_exec.argv = malloc(sizeof(char **) * 10); 			// À voir le nombre d'args max à gérer - ⚠️MALLOC ICI⚠️
	return (node);
}