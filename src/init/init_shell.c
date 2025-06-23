/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:30 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 18:53:29 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_shell(t_shell *s, char	**envp)
{
	g_status = READY;
	s->env_list = table_to_ll(envp);
	if (!s->env_list)
		return (-1);
	s->ret_value = 0;
	s->numerr = 0;
	s->pipe_count = 0;
	s->prompt = NULL;
	s->line = NULL;
	s->pwd = var_lookup(s->env_list, "PWD");
	s->old_pwd = var_lookup(s->env_list, "PWD");
	s->home = var_lookup(s->env_list, "HOME");
	s->pid_count = 0;
	s->head = NULL;
	s->root_node = NULL;
	s->current_node = NULL;
	s->root_redir = NULL;
	s->sig_mode = MINISHELL_SIGNALS;
	return (0);
}
