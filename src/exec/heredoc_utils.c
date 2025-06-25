/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:53 by timmi             #+#    #+#             */
/*   Updated: 2025/06/25 12:02:38 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(t_shell *s, t_ast *node)
{
	int	i;

	s->heredoc_fd = 0;
	i = -1;
	while (++i < node->data.s_exec.heredoc_count)
	{
		if (s->heredoc_fd > 0)
			if (close(s->heredoc_fd) < 0)
				return (-1);
		s->fd = 0;
		if (i == node->data.s_exec.heredoc_count - 1)
		{
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 1) != 0)
				return (-1);
		}
		else
		{
			if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 0) != 0)
				return (-1);
		}
		s->heredoc_fd = redir_in(s, s->heredoc_tmp, 0);
		if (s->heredoc_fd < 0)
			return (-1);
	}
	return (0);
}

void	waitheredoc(uint8_t *numerr, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		*numerr = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		*numerr = WEXITSTATUS(status);
	else
		*numerr = 1;
}
