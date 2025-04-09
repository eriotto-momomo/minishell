/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/04/09 16:06:08 by timmi            ###   ########.fr       */
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

/*Structure pour les token :
- data - La string que contien le noeud
- type - le type du token (word, pipe, redirecton, etc...)
- next - pointeur vers le prochain noeud
*/
typedef struct s_list
{
	char			*data;
	t_types			type;
	struct s_list	*next;
}					t_list;

/*			PROMPT			*/
void	prompt_loop(char *prompt);
char	*create_prompt(void);

/*		Linked list			*/
t_list	*create_node(char *data);
void	add_back(t_list	**head, char *data);
void	add_front(t_list **head, char *data);
void	free_list(t_list *head);

/*			Lexer			*/
t_list *tokenize(char *cmd);

#endif