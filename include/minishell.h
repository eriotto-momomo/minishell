/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/05/07 20:48:12 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <linux/limits.h>
# include "./struct.h"
# include "./lexer.h"
# include "./parser.h"
# include "./prompt.h"
# include "./signals.h"
# include "./utils.h"
# include "./exec.h"
# include "./builtin.h"
# include "./ht.h"
# include "../lib/libft/libft.h"

// Prompt par default utiliser si le custom prompt fail
# define DEFAULT_PROMPT "minishell-1.0$ "

// Char set de caractere qui peuvent separer des token dans une commande
# define SEPARATORS "|\"\'<>"
# define BUILTINS "cd echo env exit export pwd unset"

// HASH TABLE
# define INITIAL_CAPACITY 32 // Initial capacity of ht
# define FNV_OFFSET 14695981039346656037UL
# define FNV_PRIME 1099511628211UL

#endif
