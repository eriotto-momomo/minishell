/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/25 20:17:37 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (s->fd >= 0)
		close(s->fd);
	if (s->heredoc_fd >= 0)
		close(s->heredoc_fd);
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

void	kill_children(t_shell *s)
{
	clean_free(s);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}
