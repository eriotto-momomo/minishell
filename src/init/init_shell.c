/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:30 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 20:15:26 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_shell(t_shell *s, char	**envp)
{
	g_sig = 0;
	s->env_list = table_to_ll(envp);
	if (!s->env_list)
		return (-1);
	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		return (print_error(&s->numerr, ENOMEM));
	s->heredoc_fd = -2;
	s->fd = -2;
	s->sig_mode = -1;
	s->child_exit = 0;
	s->ret_value = 0;
	s->pipe_count = 0;
	s->numerr = 0;
	s->prompt = NULL;
	s->line = NULL;
	s->pwd = var_lookup(s->env_list, "PWD");
	s->old_pwd = var_lookup(s->env_list, "OLDPWD");
	s->home = var_lookup(s->env_list, "HOME");
	s->pid_count = 0;
	s->head = NULL;
	s->root_node = NULL;
	s->current_node = NULL;
	return (0);
}
