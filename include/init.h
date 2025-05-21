/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:27:42 by timmi             #+#    #+#             */
/*   Updated: 2025/05/21 14:50:05 by timmi            ###   ########.fr       */
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

// Struct
void init_shell(t_shell *s, char	**envp);

#endif
