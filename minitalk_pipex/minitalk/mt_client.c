/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:08 by emonacho          #+#    #+#             */
/*   Updated: 2025/03/18 18:53:29 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = ready;

void	end_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Success! Message delivered.\n", 1);
	exit(0);
}

void	ack_handler(int signal)
{
	(void)signal;
	g_ack = ready;
}

void	send_bits(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		g_ack = busy;
		if ((c >> bit) & 1)
			w_kill(server, SIGUSR1);
		else
			w_kill(server, SIGUSR2);
		while (g_ack == busy)
			usleep(100);
		usleep(100);
		bit++;
	}
}

void	send_string(char *str, pid_t server)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bits(str[i], server);
		i++;
	}
	send_bits('\0', server);
}

int	main(int ac, char *av[])
{
	t_s	s;

	if (ac != 3)
	{
		ft_putstr_fd("Error! Arguments must be server PID and message.\n", 2);
		exit(1);
	}
	if (ft_strlen(av[2]) >= 16384)
	{
		ft_putstr_fd("Error! Message is too long.\n", 2);
		exit(1);
	}
	s.server_pid = check_pid(av[1]);
	s.msg_len = ft_strlen(av[2]);
	s.str_len = ft_itoa(s.msg_len);
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, end_handler);
	send_string(s.str_len, s.server_pid);
	free(s.str_len);
	ft_putstr_fd("Sending message, please wait...\n", 1);
	send_string(av[2], s.server_pid);
	while (1)
		pause();
	return (0);
}
