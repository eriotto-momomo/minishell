/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/07/24 18:40:37 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>

//pipes.c
void	close_pipes(int count, int pipe_fd[][2]);
int		handle_pipe(t_shell *s, t_ast **node);
int		setup_pipe(int fd_in, int fd_out);

//exec.c
int		preorder_exec(t_shell *s, t_ast **node);
int		execution(t_shell *s);

//exec_utils.c
int		cmd_execution(t_shell *s, t_env *env, char **argv);
int		waiton(uint8_t *numerr, int *child_pids, int pid_count);
int		close_fds(t_ast *node);

int		write_heredoc(t_shell *s, char *path, char** eof_list, int eof_count);
int		create_heredoc(t_shell *s, char** eof_list, int eof_count);
int		unlink_tmp_files(char **tmp_files_list, int heredoc_count);
void	expand_heredoc(uint8_t numerr, t_env *env, char **str);

char	*pathfinder(t_env *env, char *cmd);
char	*path_making(t_env *env, char *cmd);

void	waitheredoc(uint8_t *numerr, pid_t pid);

#endif
