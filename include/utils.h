/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:45 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/08 15:14:58 by timmi            ###   ########.fr       */
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
t_list *create_node(char *data);
void add_back(t_list **head, char *data);
void add_front(t_list **head, char *data);
void free_list(t_list **head);
size_t count_cmd(t_list *head);

// lexer_utils.c
int is_sep(char c);

// exit_utils.c
void exit_check(t_shell *shell);
void terminate_shell(t_shell *minishell);

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
t_env	*table_to_ll(char **env);
void add_var_back(t_env **head, char *name, char *value);
#endif


// get_value (env_utils.c:128)
// ==1147406==    by 0x10BA5C: table_to_ll (env_utils.c:150)
// ==1147406==    by 0x10945F: initialize_struct (main.c:29)
// ==1147406==    by 0x10961C: main (main.c:78)

// ==1147406==    by 0x10B6E2: create_var (env_utils.c:54)
// ==1147406==    by 0x10B754: add_var_back (env_utils.c:66)
// ==1147406==    by 0x10BAA8: table_to_ll (env_utils.c:158)
// ==1147406==    by 0x10945F: initialize_struct (main.c:29)
// ==1147406==    by 0x10961C: main (main.c:78)


// ==1147406==    by 0x10B8B8: get_name (env_utils.c:106)
// ==1147406==    by 0x10BA39: table_to_ll (env_utils.c:149)
// ==1147406==    by 0x10945F: initialize_struct (main.c:29)
// ==1147406==    by 0x10961C: main (main.c:78)