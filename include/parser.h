/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/01 17:39:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser.c
t_ast	*build_ast(t_list **tok);
t_ast	*parser(t_list *tok);

// parser_add_node.c
t_ast	*add_pipe_node(t_ast *left, t_ast *right);
t_ast	*add_redir_node(t_ast *left, char *filename, int mode);
t_ast	*add_exec_node(t_list **tok);
t_ast	*ast_new_node(t_ast node);

// parser_func.c
t_ast	*parse_pipe(t_list **tok);
t_ast	*parse_line(t_list **tok);
t_ast	*parse_redir(t_list **tok, t_ast *left);
t_ast	*parse_exec(t_list **tok);

// parser_utils.c
char	*fill_exec_node(t_list *tok);
void	get_next_token(t_list **tok);
void	print_node(t_ast *ast); // 🚮TO REMOVE

// syntax analysis
int		syntax_analysis(t_list *tok);

#endif
