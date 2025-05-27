/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/27 09:21:00 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_check(t_shell *s)
{
	if (ft_strnprefix(s->head->data, "exit", ft_strlen("exit")))
		terminate_shell(s);
}

void terminate_shell(t_shell *s)
{
	if (s->head)
		free_list(&(s->head));
	if (s->root_node)
		free_ast(&(s->root_node));
	if (s->env_list)
		free_env(&(s->env_list));
	w_free((void **)&(s->line));
	w_free((void **)&(s->pwd));
	w_free((void **)&(s->old_pwd));
	w_free((void **)&(s->prompt));
	printf("Exiting minishell !\nSee you next time !\n");
	exit(0);
}
