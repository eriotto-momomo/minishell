/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:19:46 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 12:32:13 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_all_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(t_shell *s, int ac, char **av)
{
	if (ac > 2)
		return (print_custom_error(&s->numerr, 1, "too many arguments"));
	if (ac > 1)
	{
		if (is_all_digit(av[1]))
			s->numerr = (uint8_t)ft_atoi(av[1]);
		else
			print_custom_error(&s->numerr, 2, "numeric argument required");	
	}
	terminate_shell(s);
	return (0);
}
