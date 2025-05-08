/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:01 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 21:23:07 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

// BUILTINS
int		ft_cd(t_shell *s);
int		ft_echo(t_shell *s, int fd_out);
int		ft_pwd(t_shell *s);
void	ft_env(t_shell *s, int fd_out);
int		ft_unset(t_shell *s);
int		ft_export(t_shell *s);
// UTILS
char	*save_cwd(void);

#endif