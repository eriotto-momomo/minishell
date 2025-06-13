/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:45 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/13 11:39:00 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// TO REMOVE
//////////////////////////////////
void	debug_list(t_list *head);
void	print_list(t_list *head);
//////////////////////////////////

// list.c
t_list	*create_node(char *data);
int		add_back(t_list **head, char *data);
void	add_front(t_list **head, char *data);
void	free_list(t_list **head);
size_t	count_cmd(t_list *head);
size_t	env_len(t_env *h_env);

// lexer_utils.c
int is_sep(char c);

// exit_utils.c
void exit_check(t_shell *s);
void terminate_shell(t_shell *s, int error);

// free_ast.c
void	free_pipe_node(t_ast *node);
void	free_redir_node(t_ast *node);
void	free_exec_node(t_ast *node);
void	free_ast(t_ast **node);


// env
/**
 * @brief Retrieves the value of an environment variable.
 *
 * Iterates through a linked list of environment variables and returns the value
 * associated with the given name if found.
 *
 * @param h_env Pointer to the head of the linked list of environment variables.
 * @param name Name of the environment variable to search for (null-terminated string).
 * @return The value associated with the variable (char *) if found, NULL otherwise.
 * @note The returned pointer refers directly to the stored value; it is not a
 * duplicated string. Do not modify or free it unless you manage the original list.
 */
char	*ft_getenv(t_env *h_env, const char *name);
char	**env_dup(char **array);
void	free_env(t_env **h_env);

// env++

int	add_var_back(t_env **head, char *name, char *value);
#endif
