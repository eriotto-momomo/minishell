/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/23 20:07:49 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *s, int ac, char **av)
{
	int	tmp;
	
	errno = 0;
	if (ac > 2)
		return (print_error(&s->numerr, E2BIG, "exit"));
	if (ac > 1)
	{
		tmp = ft_atoi(av[1]);
		if (!tmp)
			print_error(&s->numerr, errno, "exit");
		s->numerr = (uint8_t)tmp;
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
	w_free((void **)&(s->heredoc_tmp));
	setup_signals(s, DEFAULT_SIGNALS);
}

void	terminate_shell(t_shell *s)
{
	clean_free(s);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}
