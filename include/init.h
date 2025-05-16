/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:27:42 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 19:18:58 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct	s_env t_env;
typedef struct s_shell t_shell;


// ENV
t_env	*table_to_ll(char **env);
char	*get_value(char *s);
char	*get_name(char	*s);
char	**ll_to_table(t_env *h_env);

// Struct
void init_shell(t_shell *s, char	**envp);

#endif
