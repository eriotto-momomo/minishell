/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:18 by emonacho          #+#    #+#             */
/*   Updated: 2025/03/18 18:46:34 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>

enum e_state
{
	busy,
	ready
};

typedef struct s_minitalk
{
	char	*buffer;
	int		buff_size;
	int		real_buff_size_set;
	int		i;
	int		c;
	int		bit;
	int		step;
	int		msg_len;
	char	*str_len;
	pid_t	client_pid;
	pid_t	server_pid;
}			t_s;

int		check_pid(char *str_pid);
int		reset_struct(t_s *s, int reset);
void	free_and_respond(t_s *s, int signal);
void	w_kill(pid_t pid, int signal);

#endif
