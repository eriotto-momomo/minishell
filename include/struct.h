/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:41:49 by timmi             #+#    #+#             */
/*   Updated: 2025/05/15 14:38:12 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_types
{
	WORD,
	IN_REDIR,
	OUT_REDIR,
	APP_OUT_REDIR,
	HERE_DOC,
	PIPE,
} t_types;

typedef enum	e_tag
{
	AST_PIPE,
	AST_REDIR,
	AST_EXEC
} 				t_tag;

typedef enum e_syntax_errors
{
	UNEXPECTED_TOK,
	UNMATCHED_QUOTE,
	
}				t_s_error;

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast t_ast;

typedef union	u_data
{
	struct { t_ast *parent; t_ast *left; t_ast *right; } ast_pipe;
	struct { t_ast *parent; t_ast *left; char *filename; int mode; } ast_redir;
	struct { t_ast *parent; int argc; char **argv; } ast_exec;
}				t_data;

typedef struct	s_ast
{
	t_tag		tag;
	t_data		data;
}				t_ast;

/*
Structure pour les token :
- data - La string que contien le noeud
- type - le type du token (word, pipe, redirecton, etc...)
- next - pointeur vers le prochain noeud
*/
typedef struct s_list
{
	char			*data;
	t_types			type;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_shell
{
	t_env	*env_list;
	int		err;
	char	*prompt;
	char	*line;
	char	*old_pwd;
	char	*pwd;
	t_ast	*root_node;
	t_list	*head;
}			t_shell;

#endif
