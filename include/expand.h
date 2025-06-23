/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:54:52 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 10:04:32 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand(t_shell *s, t_env *env, char **str);
int		is_in_double_quote(char *s, int j);
char	*make_prefix(t_shell *s, t_env *env, char *str, int i);
char	*get_var(t_env *env, char *s);
int		string_processing(t_shell *s, int *ac, char ***args);

#endif
