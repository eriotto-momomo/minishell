/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/22 18:11:02 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

// FORWARD DECLARATION (dis au compilateur que "t_ast")
typedef struct s_ast	t_ast;

typedef union	u_data
{
	struct { t_ast *left; t_ast *right; } ast_block;
	struct { t_ast *left; t_ast *right; } ast_pipe;
	struct { t_ast *left; t_ast *right; } ast_line;
	struct { t_ast *left; char *filename; int mode; } ast_redir;
	struct { int argc; char **argv; } ast_exec;
}				t_data;

typedef struct	s_ast
{
	t_tag		tag;
	t_data		data;
}				t_ast;

/*typedef struct	s_ast
{
	t_tag		tag;
	union		u_data
	{
		struct { t_ast *left; t_ast *right; } ast_block;
		struct { t_ast *left; t_ast *right; } ast_pipe;
		struct { t_ast *left; t_ast *right; } ast_line;
		struct { t_ast *left; char *filename; int mode; } ast_redir;
		struct { int argc; char **argv; } ast_exec;
	}			data;
}				t_ast;*/

// parser.c
t_ast	*build_ast(t_list **head);

// parser_cmd.c
// (prototypes temporaires)
t_ast	*block_cmd(t_ast *left, t_ast *right);
t_ast	*pipe_cmd(t_ast *left, t_ast *right);
t_ast	*line_cmd(t_ast *left, t_ast *right);
t_ast	*redir_cmd(t_ast *left, char *filename, int mode);
t_ast	*exec_cmd(void);

// parser_func.c
// (prototypes temporaires)
t_ast	*parse_block(t_list **head);
t_ast	*parse_pipe(t_list **head);
t_ast	*parse_line(t_list **head);
t_ast	*parse_redir(t_list **head, t_ast *cmd);
t_ast	*parse_exec(t_list **head);

// parser_utils.c
t_ast	*ast_new_node(t_ast cmd);
void	consume_token(t_list **head);
void	print_exec_args(char **node); // 🚮TO REMOVE
void	print_ast(t_ast *ast); // 🚮TO REMOVE

#endif