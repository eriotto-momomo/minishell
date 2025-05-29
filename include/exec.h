/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/05/29 13:28:07 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>
#include <sys/wait.h>

// exec.c
void	execution(t_shell *s);
int		ft_external(t_env *env, t_ast *current_node, int fd_in, int fd_out);
int		preorder_exec(t_shell *s, t_ast **current_node, int fd_in, int fd_out);
int		cmd_execution(t_env *env, char **argv);

// exec_utils.c
// char	*pathfinder(char *cmd);
int		setup_pipe(int	fd_in, int fd_out);
int		handle_pipe(t_shell *s, t_ast **current_node, int fd_in, int fd_out);
int		handle_redir(t_shell *s, t_ast **current_node, int fd_in, int fd_out);
int		handle_exec(t_shell *s, t_ast *current_node, int fd_in, int fd_out);

// redir.c
int		redirect(t_shell *s, t_ast *current_node);

// heredoc.c
int		handle_heredoc(t_shell *s, t_ast *current_node);

#endif
