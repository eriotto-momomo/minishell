/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:27:42 by timmi             #+#    #+#             */
/*   Updated: 2025/05/09 12:01:15 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// ENV
t_env	*table_to_ll(char **env);
char	*get_value(char *s);
char	*get_name(char	*s);
char	**ll_to_table(t_env *h_env);

#endif