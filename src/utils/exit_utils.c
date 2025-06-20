/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/20 10:13:35 by timmi            ###   ########.fr       */
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
		terminate_shell(s);
	}
	terminate_shell(s);
	return (0);
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
	setup_signals(s, DEFAULT_SIGNALS); // 🚨 AJOUTER SAFE CHECKS
}

void	terminate_shell(t_shell *s)
{
	clean_free(s);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}
