/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:46:53 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 14:52:30 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_fork(t_shell *s, t_env *env, t_ast *node)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = fork();
	if (pid < 0)
		return (print_error(&s->numerr, EPIPE, "fork"));
	if (pid == 0)
	{
		if (setup_pipe(node->data.s_exec.fd_in, node->data.s_exec.fd_out) == -1)
			return (print_error(&s->numerr, errno, "setup_pipe"));
		if (write_heredoc(s, node->data.s_exec.heredoc_list[i], 1) != 0)
			return (-1);
		
	}
	return (0);
}