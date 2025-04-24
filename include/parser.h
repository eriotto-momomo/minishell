/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 16:00:35 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser.c
t_ast *build_ast(t_list **head);
t_ast *parser(t_list *head);

// parser_cmd.c
// (prototypes temporaires)
t_ast *block_cmd(t_ast *left, t_ast *right);
t_ast *pipe_cmd(t_ast *left, t_ast *right);
t_ast *line_cmd(t_ast *left, t_ast *right);
t_ast	*redir_cmd(t_ast *left, char *filename, int mode);
t_ast *exec_cmd(void);

// parser_func.c
// (prototypes temporaires)
t_ast *parse_block(t_list **head);
t_ast *parse_pipe(t_list **head);
t_ast *parse_line(t_list **head);
t_ast *parse_redir(t_list **head, t_ast *cmd);
t_ast *parse_exec(t_list **head);

// parser_utils.c
t_ast	*ast_new_node(t_ast cmd);
void	consume_token(t_list **head);
void	fill_exec_node(t_list **head, t_ast *cmd, int *argc);
void	print_exec_args(char **node); // 🚮TO REMOVE
void	print_ast(t_ast *ast); // 🚮TO REMOVE

#endif
