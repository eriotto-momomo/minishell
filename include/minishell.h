/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/05/10 13:25:34 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/limits.h>
#include "./struct.h"
#include "./lexer.h"
#include "./parser.h"
#include "./prompt.h"
#include "./signals.h"
#include "./utils.h"
#include "./exec.h"
#include "./builtin.h"
#include "./wrappers.h"
#include "../lib/libft/libft.h"

// Prompt par default utiliser si le custom prompt fail
# define DEFAULT_PROMPT "minishell-1.0$ "

// Char set de caractere qui peuvent separer des token dans une commande
# define SEPARATORS "|\"\'<>"



// ENV
t_env	*create_var(char *name, char	*value);
void	add_var_back(t_env **head, char *name, char *value);
void	del_var(t_env **head, t_env **target);

#endif
