/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:29:45 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 13:33:40 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	reset_free(t_shell *s);
void	clean_free(t_shell *s);
int		ft_exit(t_shell *s, int ac, char **av);
void	terminate_shell(t_shell *s);
void	free_pipe_node(t_ast *node);
void	free_exec_node(t_ast *node);
void	free_ast(t_ast **node);
void	v_switch(char **s, char *new_s);
char	*ft_getenv(t_env *h_env, const char *name);
void	free_env(t_env **h_env);
int		add_var_back(t_env **head, char *name, char *value);
int		is_sep(char c);
size_t	count_var(t_env *head);
char	**ltotable(t_env *env);
t_env	*create_var(char *name, char	*value);
void	del_var(t_env **head, t_env **target);
int		perfect_match(char *s1, char *s2);

#endif
