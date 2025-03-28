/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:10 by emonacho          #+#    #+#             */
/*   Updated: 2025/03/18 18:53:21 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_reset = -1;

void	fill_buffer(t_s *s)
{
	if (s->i < s->buff_size)
	{
		s->buffer[s->i] = s->c;
		(s->i)++;
	}
	if (s->c == '\0')
	{
		s->buffer[s->i] = '\0';
		if (s->real_buff_size_set == 1)
		{
			write(1, s->buffer, s->buff_size);
			write(1, "\n", 1);
			w_kill(s->client_pid, SIGUSR1);
			free_and_respond(s, SIGUSR2);
			reset_struct(s, -1);
			g_reset = -1;
		}
		else
		{
			s->buff_size = ft_atoi(s->buffer);
			s->real_buff_size_set = 1;
			free_and_respond(s, SIGUSR1);
			g_reset = 0;
		}
	}
}

// 16384 = 16ko
int	msg_is_valid(t_s *s)
{
	if (s->buff_size <= 0 || s->buff_size >= 16384)
	{
		ft_putstr_fd("Error! Message too long or too short. Please try again.\n",
			2);
		free_and_respond(s, SIGUSR2);
		reset_struct(s, -1);
	}
	s->buffer = ft_calloc(sizeof(char), s->buff_size + 1);
	if (s->buffer == NULL)
		exit(1);
	s->buffer[0] = s->c;
	s->i = 1;
	return (1);
}

void	bit_decoder(int signal, t_s *s)
{
	if (signal == SIGUSR1)
		s->c |= (1 << s->bit);
	else if (signal == SIGUSR2)
		s->c &= ~(1 << s->bit);
	(s->bit)++;
}

void	msg_handler(int signal, siginfo_t *info, void *more_info)
{
	static t_s	s;

	(void)more_info;
	if (g_reset == 0 || g_reset == -1)
		g_reset = reset_struct(&s, g_reset);
	if (s.client_pid == 0)
		s.client_pid = info->si_pid;
	bit_decoder(signal, &s);
	w_kill(s.client_pid, SIGUSR1);
	if (s.bit == CHAR_BIT)
	{
		s.bit = 0;
		if (!s.step)
		{
			msg_is_valid(&s);
			s.step = 1;
		}
		else if (s.step)
			fill_buffer(&s);
		s.c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_printf("SERVER PID=%d\n", pid);
	sa.sa_sigaction = msg_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
