/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/07/26 17:01:40 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>

int		close_pipes(t_ast *node, int pipe_fd[][2], int pipe_count);

int		handle_pipe(t_shell *s, t_ast **node);
int		setup_pipe(int fd_in, int fd_out);

int		preorder_exec(t_shell *s, t_ast **node);
int		execution(t_shell *s);

int		cmd_execution(t_shell *s, t_env *env, char **argv);
int		waiton(uint8_t *numerr, int *child_pids, int pid_count);
int		close_fds(t_ast *node);

int		write_heredoc(t_shell *s, char *path, char **eof_list, int eof_count);
int		unlink_tmp_files(char **tmp_files_list, int heredoc_count);

char	*pathfinder(t_env *env, char *cmd);
char	*path_making(t_env *env, char *cmd);

#endif
