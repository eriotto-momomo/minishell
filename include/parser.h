/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/27 16:44:34 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser_add_node.c
t_ast	*add_pipe_node(t_ast *left, t_ast *right);
t_ast	*add_redir_node(t_ast *left, char *filename, int mode);
t_ast	*add_exec_node(t_list **tok);
t_ast	*ast_new_node(t_ast node);

// parser_main.c
/**
 * @file parser.c
 * @brief Parses the token list and creates an Abstract Syntax Tree (AST).
 *
 * The `parser` function analyzes the list of tokens to validate the syntax.
 * If the syntax is correct, it constructs an AST and frees the token list.
 * Otherwise, it frees the token list and returns an error code.
 *
 * @param s A pointer to the main shell structure containing the token list and the root AST node.
 *
 * @return
 * - 0 if the syntax is valid and the AST is successfully created.
 * - 1 if a syntax error is detected.
 *
 * @note The token list is always freed by this function, regardless of the outcome.
 */
int		parser(t_shell *s);
t_ast	*build_ast(t_list **tok);
void	print_preorder(t_ast *node);

// parser_func.c
t_ast	*parse_pipe(t_list **tok);
t_ast	*parse_line(t_list **tok);
t_ast	*parse_redir(t_list **tok, t_ast *left);
t_ast	*parse_exec(t_list **tok);

// parser_utils.c
char	*fill_exec_node(t_list *tok);
int		get_next_token(t_list **tok);
int		count_args(t_list *tok);
void	print_node(t_ast *ast); // 🚮TO REMOVE

// syntax_analysis.c
int		syntax_analysis(t_list *tok);

#endif
