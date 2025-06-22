/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:41:49 by timmi             #+#    #+#             */
/*   Updated: 2025/06/22 13:48:42 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum	e_mode
{
	RESET_PROMPT,
	HEREDOC_PROMPT
};

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

typedef struct s_token
{
	char			*data;
	t_types			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

// FORWARD DECLARATION (dis au compilateur que "t_sig" existe)
typedef struct	s_signals t_sig;
struct	s_termios;

typedef struct s_shell
{
	t_env	*env_list;
	int		ret_value;
	char	*prompt;
	char	*line;
	t_env	*old_pwd;
	t_env	*pwd;
	t_env	*home;
	t_ast	*current_node;
	t_ast	*root_node;
	t_token	*head;
	t_sig	*sig;
	pid_t	child_pids[MAX_CMDS];
	int		pid_count;
	int		pipe_fd[MAX_CMDS][2];
	int		pipe_count;
	char	*heredoc_tmp;
	char	**heredoc_list;
	int		heredoc_count;
	int		fd;
	int		final_output_fd;	// 🚨USELESS❔
	int		sig_mode;
	int		stdin_save;
	int		stdout_save;
	int		node_initialized;
	t_ast	*root_redir;
	uint8_t	numerr;
}			t_shell;

#endif
