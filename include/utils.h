/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:45 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/16 13:54:32 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// TO REMOVE
//////////////////////////////////
int debug(char *path);
void print_list(t_list *head);
//////////////////////////////////

// list.c
t_list	*create_node(char *data);
void	add_back(t_list **head, char *data);
void	add_front(t_list **head, char *data);
void	free_list(t_list **head);
size_t	count_cmd(t_list *head);
size_t	env_len(t_env *h_env);

// lexer_utils.c
int is_sep(char c);

// exit_utils.c
void exit_check(t_shell *s);
void terminate_shell(t_shell *s);

// free_ast.c
void	free_pipe_node(t_ast *node);
void	free_redir_node(t_ast *node);
void	free_exec_node(t_ast *node);
void	free_ast(t_ast **node);


// env
char	*ft_getenv(t_env *h_env, const char *name);
char	**env_dup(char **array);
void	free_env(t_env **h_env);

// env++

void add_var_back(t_env **head, char *name, char *value);
#endif
