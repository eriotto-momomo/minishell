/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:05 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/16 08:59:18 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

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
int tokenize(t_list **head, char *cmd);

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
char *get_word(char *cmd);

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
char *get_sep(char *cmd);

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
char	*get_quote(char *cmd);
int   get_token_id(char *token);
void	lexer(t_shell *s);
char  *get_el(char *cmd);
#endif
