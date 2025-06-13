/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:41:49 by timmi             #+#    #+#             */
/*   Updated: 2025/06/13 11:38:48 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H


enum	e_mode
{
	RESET_PROMPT,
	HEREDOC_PROMPT
};

/*
* L'enum 'e_signal' est utilisee pour indiquer le type de signal recu au shell par la
* variable globale 'g_sig'
* CTRLC = 'CTRL + C'
* CTRLD = 'CTRL + D'
* CTRLBACK = 'CTRL + \'
*/
enum e_signal
{
	CTRLC,
	CTRLD,
	CTRLBACK
};

typedef struct	s_signals
{
	int	signal;
}	t_sig;

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
	PIPE_NODE,
	EXEC_NODE
} 				t_tag;


//	NO_ERRORS = 0
//	UNEXPECTED_TOK = 1
//	UNMATCHED_QUOTE = 2
typedef enum e_errors_return
{
	NO_ERRORS,
	UNEXPECTED_TOK,
	UNMATCHED_QUOTE,
}				t_errors;

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast t_ast;

typedef union	u_data
{
	struct { t_ast *left; t_ast *right; } pipe;
	struct { int argc; char **argv; int fd_in; int fd_out; int heredoc_count; char	**heredoc_list; } exec;
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
	int		ret_value;
	char	*prompt;
	char	*line;
	t_env	*old_pwd; // !! Holds the adress to the element in the env list
	t_env	*pwd; // !! Holds the adress to the element in the env list
	t_env	*home; // !! Holds the adress to the element in the env list
	t_ast	*current_node;
	t_ast	*root_node;
	t_list	*head;
	t_sig	*sig;
	char	*heredoc_tmp;
	char	**heredoc_list;
	int		heredoc_count;
	int		fd;
	int		final_output_fd;
	int		stdin_save;
	int		stdout_save;
	int		node_initialized;
	t_ast	*root_redir;
	int		pipefd[2]; // 🚨 NORM OK❔ Besoin d'un malloc❔
}			t_shell;

#endif
