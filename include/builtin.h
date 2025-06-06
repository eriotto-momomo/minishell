/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:01 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/06 07:42:20 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define ENV "env"
# define UNSET "unset"
# define EXPORT "export"

// BUILTINS
int	ft_cd(t_shell *s);
int	ft_echo(t_ast **current_node, int fd_out);
int	ft_pwd(t_shell *s, int	fd_out);
int	ft_env(t_shell *s, int fd_out);
int	ft_unset(t_shell *s);
int	ft_export(t_env *env, char **args);
// UTILS
char	*save_cwd(void);

#endif
