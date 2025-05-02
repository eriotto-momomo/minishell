/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:45 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/01 14:37:56 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

// TO REMOVE
//////////////////////////////////
int debug(char *path);
void print_list(t_list *head);
//////////////////////////////////

// list.c
t_list *create_node(char *data);
void add_back(t_list **head, char *data);
void add_front(t_list **head, char *data);
void free_list(t_list *head);
size_t count_cmd(t_list *head);

// lexer_utils.c
int is_sep(char c);

// EXIT
void exit_check(t_shell *shell);
void terminate_shell(t_shell *minishell);

// free_ast.c
void	free_ast(t_ast *ast);

#endif
