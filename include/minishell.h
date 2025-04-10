/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/04/10 11:00:09 by timmi            ###   ########.fr       */
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

/*			GENERAL			*/
int	is_sep(char c);

typedef struct	s_builtin
{
	char		*func_list;
}				t_builtin;

typedef struct	s_shell
{
	t_builtin	*builtins;
	char		**env;
}				t_shell;

/*			PROMPT			*/
void	prompt_loop(char *prompt, t_shell *s);
/**
 * @brief	Create a shell prompt using the user's name and the host/session name.
 *
 * @details	This function retrieves the current user's name and the hostname from
 *			the environment variables. If the hostname is not available, it attempts
 *			to use the session manager name instead, trimming it if necessary.
 *			The prompt is then built by combining the user and host/session name.
 *			If neither is available, a default prompt "minishell-1.0" is used.
 *
 * @return	A dynamically allocated string containing the full shell prompt.
 *			The caller is responsible for freeing it.
 */
char	*create_prompt(void);

/*			PARSER			*/
int	simple_token_interpreter(t_shell *s, char *line_read);

/*		Linked list			*/
t_list	*create_node(char *data);
void	add_back(t_list	**head, char *data);
void	add_front(t_list **head, char *data);
void	free_list(t_list *head);

/*			Lexer			*/
/**
 * @brief Tokenizes a command string into a linked list of elements.
 *
 * This function parses the input string `cmd`, skipping whitespace characters
 * (as determined by `is_space`), and extracts tokens using the `get_el` function.
 * Each token is then appended to a linked list using `add_back`.
 * If an error occurs (e.g., memory allocation fails), the partially built list
 * is freed using `free_list` and the function returns NULL.
 *
 * @param cmd The command string to tokenize.
 * @return t_list* A linked list containing the extracted tokens, or NULL on error.
 *
 * @note This function assumes that `is_space`, `get_el`, `ft_strlen`,
 * `add_back`, and `free_list` are implemented elsewhere.
 */
t_list	*tokenize(char *cmd);
/**
 * @brief Extracts a word (non-space, non-separator sequence) from the command.
 *
 * Starting at index `i`, this function reads characters from `cmd` until it
 * reaches a space or a separator (as defined by `is_space` and `is_sep`).
 * The result is a newly allocated string containing the word.
 *
 * @param cmd The command string to parse.
 * @param i The starting index of the word.
 * @return char* A newly allocated string containing the word,
 * or NULL on allocation failure.
 *
 * @note The caller is responsible for freeing the returned string.
 */
char	*get_word(char *cmd, int i);

/**
 * @brief Extracts a single character separator from the command.
 *
 * This function allocates and returns a string containing only the character
 * at the given index `i` of `cmd`, assumed to be a separator.
 *
 * @param cmd The command string to parse.
 * @param i The index of the separator character.
 * @return char* A newly allocated string with the separator character,
 * or NULL on allocation failure.
 *
 * @note The caller is responsible for freeing the returned string.
 */
char	*get_sep(char *cmd, int i);

/**
 * @brief Extracts a quoted string from the command.
 *
 * This function starts at the given index `i` of the `cmd` string and extracts
 * a substring enclosed in matching single or double quotes. It includes the
 * opening and closing quote characters in the result.
 *
 * @param cmd The command string to parse.
 * @param i The starting index of the quoted string.
 * @return char* A newly allocated string containing the quoted substring,
 * or NULL on allocation failure.
 *
 * @note The caller is responsible for freeing the returned string.
 */
char	*get_quote(char *cmd, int i);

#endif