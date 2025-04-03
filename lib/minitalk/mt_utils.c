/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/03 17:19:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	free_and_respond(t_s *s, int signal)
{
	if (s->buffer != NULL)
		free(s->buffer);
	s->buffer = NULL;
	w_kill(s->client_pid, signal);
}

int	reset_struct(t_s *s, int reset)
{
	if (reset == -1)
	{
		s->buff_size = 5;
		s->real_buff_size_set = -1;
	}
	s->i = 0;
	s->c = 0;
	s->bit = 0;
	s->step = 0;
	s->msg_len = 0;
	s->client_pid = 0;
	return (1);
}

int	check_pid(char *str_pid)
{
	int		i;
	pid_t	pid;

	pid = ft_atoi(str_pid);
	if (pid <= 0)
	{
		ft_putstr_fd("Error! Invalid PID.\n", 2);
		exit(1);
	}
	i = 0;
	while (str_pid[i] != '\0')
	{
		if (!ft_isdigit(str_pid[i]))
		{
			ft_putstr_fd("Error! PID must be a digit.\n", 2);
			exit(1);
		}
		i++;
	}
	return (pid);
}
