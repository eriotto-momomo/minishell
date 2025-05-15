/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/05/15 12:23:15 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>
#include <sys/wait.h>

// exec.c
void	cmd_execution(char **argv);
void	in_pipe(int *p, t_ast *node);
int		simple_cmd(t_shell *s);
int		ft_extern(t_shell *s);

// redir.c
int	test_redir(t_ast *node);

#endif
