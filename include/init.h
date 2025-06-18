/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:27:42 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 09:30:33 by c4v3d            ###   ########.fr       */
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
int     init_shell(t_shell *s, char	**envp);

#endif
