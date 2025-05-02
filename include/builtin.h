/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:01 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/02 10:57:56 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

// BUILTINS
int ft_echo(char **args, int fd_out);
int	ft_cd(t_shell *s);

// UTILS
char	*save_cwd(void);

#endif