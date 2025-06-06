/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/06 14:13:16 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser_add_node.c
int		add_command(t_ast **node, t_list **tok);
int		add_redir(t_ast **node, t_list **tok);
t_ast	*add_exec_node(t_list **tok);
t_ast	*add_pipe_node(t_ast *left, t_ast *right);
t_ast	*new_ast_node(t_ast node);

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
t_ast	*parse_exec(t_list **tok);
void	get_next_pipe(t_list **tok);
int		get_next_token(t_list **tok);

// parser_utils.c
int		redir_out(int redir_mode, char *filename, int current_redir);
int		redir_in(char *filename, int current_redir);
t_ast	*new_ast_node(t_ast node);
int		copy_tokens(t_list **tok, int token_type, int size, char **array);
//int		copy_tokens(t_list **tok, int argc, char **argv);
int		count_tokens(t_list **tok, int token_type);

void	print_node(t_ast *ast); // 🚮TO REMOVE

// syntax_analysis.c
int		syntax_analysis(t_list *tok);

#endif
