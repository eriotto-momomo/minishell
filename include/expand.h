/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/05/30 15:21:51 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

//UTILS
int		is_in_env(t_env	*env, char *var);
size_t	offset_calc(char *str);
int		expand(t_env *env, char **str);

// Word processing
int	string_processing(t_shell *s, char **args);

#endif
