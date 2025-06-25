/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:01 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/25 11:21:21 by timmi            ###   ########.fr       */
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

int		ft_cd(t_shell *s, int ac, char **av);
int		ft_echo(t_shell *s, t_ast **current_node, int fd_out);
int		ft_pwd(t_shell *s, int fd_out);
int		ft_env(t_shell *s, t_env *env, int fd_out);
int		ft_unset(t_shell *s, int ac, char **av);
int		ft_export(t_shell *s, t_env **env, t_ast *node);
int		ft_exit(t_shell *s, int ac, char **av);
char	*save_cwd(void);
int		replace_var(t_env **var, char *value);
t_env	*var_lookup(t_env *env, char *target);

#endif
