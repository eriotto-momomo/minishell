/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/06/05 13:19:53 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand(t_env *env, char *str);
int		var_expansion(t_env * env, char **s);
int		is_in_double_quote(char *s, int j);
char	*make_prefix(t_env *env, char *str, int i);
char	*get_var(t_env *env, char *s);


// Word processing
int	string_processing(t_shell *s, char **args);

#endif
