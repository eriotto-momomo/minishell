/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:53 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 16:58:48 by timmi            ###   ########.fr       */
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
		s->heredoc_fd = redir_in(s->heredoc_tmp, 0);				
		if (s->heredoc_fd < 0)
			return (-1);
	}
	return (s->heredoc_fd);
}
