/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 19:24:57 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

void	var_expansion(t_shell *s, char **args);

//UTILS
int		is_in_env(t_env	*env, char *var);
size_t	offset_calc(char *str);
void	expand(t_env *env, char **str);

#endif
