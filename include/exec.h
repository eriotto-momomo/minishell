/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/06/26 10:28:35 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>

int		close_fd(t_ast *node);
int		interrupt_heredoc(t_shell *s);
int		execution(t_shell *s);
int		ft_external(t_shell *s, t_env *env, t_ast *current_node);
int		preorder_exec(t_shell *s, t_ast **current_node);
int		cmd_execution(t_shell *s, t_env *env, char **argv);
char	*pathfinder(t_env *env, char *cmd);
char	*path_making(t_env *env, char *cmd);
int		setup_pipe(int fd_in, int fd_out);
int		close_pipes(t_ast *node, int pipe_fd[][2], int pipe_count);
int		handle_pipe(t_shell *s, t_ast **current_node);
int		handle_exec(t_shell *s, t_ast *current_node);
int		interrupt_heredoc(t_shell *s);
int		open_heredoc(t_shell *s);
int		is_delimiter(char *line, char *delimiter);
int		put_in_heredoc(char *line, int fd);
int		heredoc_loop(t_shell *s, t_ast *node);
int		write_heredoc(t_shell *s, char *delimiter, int to_expand);
int		handle_heredoc(t_shell *s, t_ast *node);
int		heredoc_loop(t_shell *s, t_ast *node);
void	waitheredoc(uint8_t *numerr, pid_t pid);

#endif
