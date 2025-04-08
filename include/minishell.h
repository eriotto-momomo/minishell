/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/04/08 17:07:03 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include "../lib/libft/libft.h"

// Prompt par default utiliser si le custom prompt fail
# define DEFAULT_PROMPT "minishell-1.0$ "
// Char set de caractere qui peuvent separer des token dans une commande
# define SEPARATORS "|\"\'<>"
/*
 Attribution d'une valeur constante pour chaque token
 - WORD =	0
 - PIPE =	1
 - REDIR =	2
*/
typedef enum e_types
{
	WORD,
	PIPE,
	REDIR
}	t_types;

typedef struct s_list
{
	char			*value;
	t_types			type;
	struct s_list	*next;
}					t_list;

/*			PROMPT			*/
void	prompt_loop(char *prompt);
char	*create_prompt(void);

#endif