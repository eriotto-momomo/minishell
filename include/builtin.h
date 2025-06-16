/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:01 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/16 10:54:14 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define CD "cd"
# define FT_ECHO "echo"
# define PWD "pwd"
# define ENV "env"
# define UNSET "unset"
# define EXPORT "export"

// BUILTINS
int	ft_cd(t_env *pwd, t_env *oldowd, t_env *home, t_ast *node);
int	ft_echo(t_ast **current_node, int fd_out);
int	ft_pwd(t_shell *s, int	fd_out);
int	ft_env(t_env *env, int fd_out);
int	ft_unset(t_shell *s);
int	ft_export(t_env **env, int ac, char **args, int fd);
// UTILS
char	*save_cwd(void);
int		replace_var(t_env **var, char *value);
t_env	*var_lookup(t_env *env, char *target);

#endif
