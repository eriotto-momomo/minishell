/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/24 16:33:06 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// parser.c
t_ast *parse_tokens(t_list **head);
t_ast *parser(t_list *head);

// parser_cmd.c
// (prototypes temporaires)
t_ast *block_cmd(t_ast *left, t_ast *right);
t_ast *pipe_cmd(t_ast *left, t_ast *right);
t_ast *line_cmd(t_ast *left, t_ast *right);
t_ast *redir_cmd(t_ast *cmd, char *file_name, int mode, int fd);
t_ast *exec_cmd(void);

// parser_func.c
// (prototypes temporaires)
t_ast *parse_block(t_list **head);
t_ast *parse_pipe(t_list **head);
t_ast *parse_line(t_list **head);
t_ast *parse_redir(t_list **head, t_ast *cmd);
t_ast *parse_exec(t_list **head);

// parser_utils.c
t_ast *ast_new_node(t_ast cmd);

// syntax analysis
int	syntax_analysis(t_list *token);

#endif