/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:41:49 by timmi             #+#    #+#             */
/*   Updated: 2025/04/24 13:53:50 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

/*
 Attribution d'une valeur constante pour chaque token
 - WORD =	0
 - PIPE =	1
 - REDIR =	2
*/
typedef enum e_types
{
	WORD,
	IN_REDIR,
	OUT_REDIR,
	APP_OUT_REDIR,
	HERE_DOC,
	PIPE,
	REDIR
} t_types;

// ⚠️👷‍♂️ Travail en cours, fonctions et structures probablement à modifier

// Adapté de: https://keleshev.com/abstract-syntax-tree-an-example-in-c/
typedef enum	e_tag
{
	AST_BLOCK,
	AST_PIPE,
	AST_LINE,
	AST_REDIR,
	AST_EXEC
} 				t_tag;

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast t_ast;

typedef struct	s_ast
{
	t_tag		tag;
	union		u_data
	{
		struct { t_ast *left; t_ast *right; } ast_block;
		struct { t_ast *left; t_ast *right; } ast_pipe;
		struct { t_ast *left; t_ast *right; } ast_line;
		struct { t_ast *left; t_ast *right; } ast_redir;
		struct { int argc; char **argv; } ast_exec;
	}			data;
}				t_ast;

/*
Structure pour les token :
- data - La string que contien le noeud
- type - le type du token (word, pipe, redirecton, etc...)
- next - pointeur vers le prochain noeud
*/
typedef struct s_list
{
	char *data;
	t_types type;
	struct s_list *next;
	struct s_list *prev;
} t_list;

typedef struct s_shell
{
	char	**env;
	int		cmd_count;
	char	*line;
	t_ast	*root_node;
	t_list	*head;
}			t_shell;

#endif
