/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/05/13 23:05:00 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>
#include <sys/wait.h>

void	cmd_execution(char **argv);
void	in_pipe(int *p, t_ast *node);
int		simple_cmd(t_shell *s);
int		ft_extern(t_shell *s);

int	execution(t_ast *current_node, int fd_in, int fd_out);

#endif