/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/19 19:53:31 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Adapté de: https://keleshev.com/abstract-syntax-tree-an-example-in-c/
// À vérifier (et checker si OK avec norm)...
/* This macro ties together the matching identifiers from the enum, the struct,
* and the data members. */
#define AST_NEW_NODE(tag, ...) \
	ast_new_node((t_ast){t_tag, {.t_tag=(struct t_tag){__VA_ARGS__}}})

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast	t_ast;

// Adapté de: https://keleshev.com/abstract-syntax-tree-an-example-in-c/
// À vérifier...
typedef struct s_ast
{
	struct	t_ast
	{
		enum e_tag
		{
			AST_BLOCK,
			AST_PIPE,
			AST_LINE,
			AST_REDIR,
			AST_EXEC
		} t_tag;
		union u_data
		{	// Contenu des structures à adapter ... ? Plus de données à passer dans `s_ast_exec`?
			struct s_ast_block { t_ast *left; t_ast *right; } ast_block;
			struct s_ast_pipe { t_ast *left; t_ast *right; } ast_pipe;
			struct s_ast_line { t_ast *left; t_ast *right; } ast_line;
			struct s_ast_redir { t_ast *left; t_ast *right; } ast_redir;
			struct s_ast_exec { t_ast *left; t_ast *right; } ast_exec;
		} t_data;
	  } t_ast;
}			t_ast;

// parser.c


// parser_cmd.c


// parser_func.c


// parser_utils.c
t_ast	*ast_new_node(t_ast ast);

#endif