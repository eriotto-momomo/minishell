/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:30 by timmi             #+#    #+#             */
/*   Updated: 2025/06/13 11:37:54 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_shell(t_shell *s, char	**envp)
{
	s->env_list = table_to_ll(envp);
	if (!s->env_list)
		terminate_shell(s, errno);
	s->ret_value = 0;
	s->prompt = NULL;
	s->line = NULL;
	s->pwd = var_lookup(s->env_list, "PWD");
	s->old_pwd = var_lookup(s->env_list, "ODLPWD");
	s->home = var_lookup(s->env_list, "PWD");
	s->head = NULL;
	s->root_node = NULL;
	s->current_node = NULL;
	s->root_redir = NULL;
}
