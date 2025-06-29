/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 09:37:05 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand(uint8_t numerr, t_env *env, char **str);
int		is_in_double_quote(char *s, int j);
char	*make_prefix(uint8_t numerr, t_env *env, char *str, int i);
char	*get_var(uint8_t numerr, t_env *env, char *s);
int		string_processing(t_shell *s, int *ac, char ***args);
int		trim_quote(char **s, int i, int j);
int		is_valid_var_start(char c);

#endif
