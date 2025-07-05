/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/07/05 14:34:48 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_CMDS 256

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <fcntl.h>
# include <linux/limits.h>
# include "./error.h"
# include "./init.h"
# include "./struct.h"
# include "./loop.h"
# include "./lexer.h"
# include "./parser.h"
# include "./prompt.h"
# include "./signals.h"
# include "./utils.h"
# include "./builtin.h"
# include "./expand.h"
# include "./exec.h"
# include "../lib/libft/libft.h"

// Default prompt, used when custom prompt fails
# define DEFAULT_PROMPT "minishell-1.0$ "

// Default location of all the temporary files created by minishell
# define HEREDOC_FILE_PATH ".heredoc_tmp.txt"

// Char set of characters that minishell interpret as operators
# define SEPARATORS "|<>"

extern volatile sig_atomic_t	g_sig;

// ENV
t_env	*create_var(char *name, char	*value);
void	del_var(t_env **head, t_env **target);

#endif
