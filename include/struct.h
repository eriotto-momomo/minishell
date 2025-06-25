/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:41:49 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 15:03:36 by emonacho         ###   ########.fr       */
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
}	t_types;

typedef enum e_tag
{
	PIPE_NODE,
	EXEC_NODE
}	t_tag;

// FORWARD DECLARATION (dis au compilateur que "t_ast" existe)
typedef struct s_ast	t_ast;

typedef union u_data
{
	struct
	{
		t_ast	*left;
		t_ast	*right;
	}	s_pipe;
	struct
	{
		int		ac;
		char	**av;
		int		fd_in;
		int		fd_out;
		int		heredoc_count;
		char	**heredoc_list;
	}	s_exec;
}	t_data;

typedef struct s_ast
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

typedef struct s_env
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
	t_env	*old_pwd;
	t_env	*pwd;
	t_env	*home;
	t_ast	*current_node;
	t_ast	*root_node;
	t_token	*head;
	pid_t	child_pids[MAX_CMDS];
	struct termios	term_backup;
	int		pid_count;
	int		pipe_fd[MAX_CMDS][2];
	int		pipe_count;
	char	*heredoc_tmp;
	int		heredoc_fd;
	int		child_exit;
	int		fd;
	int		sig_mode;
	uint8_t	numerr;
	int		tok_rdir;
	int		tok_pipe;
	int		tok_word;
}			t_shell;

#endif
