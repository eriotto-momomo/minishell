/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:02:47 by timmi             #+#    #+#             */
/*   Updated: 2025/05/12 11:33:18 by emonacho         ###   ########.fr       */
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
void	test_redir(t_shell *s);

#endif