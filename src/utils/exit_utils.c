/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/18 15:15:04 by emonacho         ###   ########.fr       */
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
	setup_signals(s, MINISHELL_SIGNALS);
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
	w_free((void **)&(s->tmp_files_list));
	if (s->env_list)
		free_env(&(s->env_list));
	w_free((void **)&(s->line));
	w_free((void **)&(s->prompt));
	setup_signals(s, MINISHELL_SIGNALS);
}

void	terminate_shell(t_shell *s)
{
	clean_free(s);
	if (s->tmp_files_list != NULL)
		unlink_tmp_files(s->tmp_files_list, s->heredoc_count);
	w_free((void **)&(*s->tmp_files_list));
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (s->numerr)
		exit(s->numerr);
	exit(EXIT_SUCCESS);
}

void	kill_children(t_shell *s)
{
	clean_free(s);
	if (s->numerr)
		exit((uint8_t)s->numerr);
	exit(EXIT_SUCCESS);
}
