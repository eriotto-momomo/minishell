/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 17:52:03 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>
#include <sys/wait.h>

// exec.c
int		close_fd(t_ast *node);
void	execution(t_shell *s);
int		ft_external(t_shell *s, t_env *env, t_ast *current_node);
int		preorder_exec(t_shell *s, t_ast **current_node);
int		cmd_execution(t_shell *s, t_env *env, char **argv);

// exec_utils.c
// char	*pathfinder(char *cmd);
int		setup_pipe(int	fd_in, int fd_out);
int		handle_pipe(t_shell *s, t_ast **current_node);
int		handle_exec(t_shell *s, t_ast *current_node);

// heredoc.c
int		write_heredoc(t_shell *s, char *delimiter, int to_expand);
int		handle_heredoc(t_shell *s, t_ast *node);

#endif
