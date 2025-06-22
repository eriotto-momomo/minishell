/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/22 18:19:43 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *s, int ac, char **av)
{
	int	i;

	i = 0;
	errno = 0;
	if (ac > 2)
		return (print_error(&s->numerr, E2BIG, "exit"));
	if (ac > 1)
	{
		while (av[1][i])
			if (!ft_isdigit(av[1][i++]))
				return (print_error(&s->numerr, EINVAL, "exit"));
		s->numerr = (uint8_t)ft_atoi(av[1]);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		terminate_shell(s);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	terminate_shell(s);
	return (0);
}

void	reset_free(t_shell *s)
{
	if (s->head)
		free_token_list(&(s->head));
	if (s->root_node)
		free_ast(&(s->root_node));
	w_free((void **)&(s->line));
}

void	clean_free(t_shell *s)
{
	if (s->head)
		free_token_list(&(s->head));
	if (s->root_node)
		free_ast(&(s->root_node));
	if (s->env_list)
		free_env(&(s->env_list));
	w_free((void **)&(s->line));
	w_free((void **)&(s->prompt));
	setup_signals(s, DEFAULT_SIGNALS);
}

void	terminate_shell(t_shell *s)
{
	clean_free(s);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}
