/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:05 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/22 17:37:01 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
}					t_list;

/**
 * @brief Tokenizes a command string into a linked list of elements.
 *
 * This function parses the input string `cmd`, skipping whitespace characters
 * (see `ft_isspace`), and extracts tokens using the `get_el` function.
 * Each token is then appended to a linked list using `add_back`.
 * If an error occurs (e.g., memory allocation fails), the partially built list
 * is freed using `free_list` and the function returns NULL.
 *
 * @param cmd The command string to tokenize.
 * @return t_list* A linked list containing the sliced tokens, or NULL on error.
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

int		get_token_id(char *token);

#endif