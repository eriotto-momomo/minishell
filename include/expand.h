/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 16:29:16 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand(t_env *env, char **str);
int		is_in_double_quote(char *s, int j);
char	*make_prefix(t_env *env, char *str, int i);
char	*get_var(t_env *env, char *s);


// Word processing
int	string_processing(t_shell *s,int *ac, char ***args);

#endif
