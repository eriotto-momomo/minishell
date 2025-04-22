/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/22 09:08:32 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

// ⚠️👷‍♂️ Travail en cours, fonctions et structures probablement à modifier

// Adapté de: https://keleshev.com/abstract-syntax-tree-an-example-in-c/
typedef enum e_tag
{
	AST_BLOCK,
	AST_PIPE,
	AST_LINE,
	AST_REDIR,
	AST_EXEC
} t_tag;

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast t_ast;

typedef struct s_ast
{
	t_tag tag;
	union u_data
	{
		struct
		{
			t_ast *left;
			t_ast *right;
		} ast_block;
		struct
		{
			t_ast *left;
			t_ast *right;
		} ast_pipe;
		struct
		{
			t_ast *left;
			t_ast *right;
		} ast_line;
		struct
		{
			t_ast *left;
			t_ast *right;
		} ast_redir;
		struct
		{
			int argc;
			char **argv;
		} ast_exec;
	} data;
} t_ast;

// parser syntax analysis
int syntax_analysis(t_list *token);

// parser.c
t_ast *parse_tokens(t_list **head);
t_ast *parser(t_list *head);

// parser_cmd.c
// (prototypes temporaires)
t_ast *block_cmd(t_ast *left, t_ast *right);
t_ast *pipe_cmd(t_ast *left, t_ast *right);
t_ast *line_cmd(t_ast *left, t_ast *right);
t_ast *redir_cmd(t_ast *cmd, char *file_name, int mode, int fd);
t_ast *exec_cmd(void);

// parser_func.c
// (prototypes temporaires)
t_ast *parse_block(t_list **head);
t_ast *parse_pipe(t_list **head);
t_ast *parse_line(t_list **head);
t_ast *parse_redir(t_list **head, t_ast *cmd);
t_ast *parse_exec(t_list **head);

// parser_utils.c
t_ast *ast_new_node(t_ast cmd);

#endif