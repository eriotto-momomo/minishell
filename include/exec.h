/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 19:00:21 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>
#include <sys/wait.h>

// exec.c
int	execution(t_shell *s, t_ast **current_node, int fd_in, int fd_out);
int	cmd_execution(char **argv);

// exec_utils.c
char	*pathfinder(char *cmd);
void	handle_pipe(int	fd_in, int fd_out);

// redir.c
int		redirect(t_shell *s);

#endif
