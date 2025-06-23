/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:23 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 11:10:52 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_out(int redir_mode, char *filename, int current_redir)
{
	int	fd_out;

	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
			return (-1);
	}
	if (redir_mode == OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_mode == APP_OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd_out);
}

int	redir_in(char *filename, int current_redir)
{
	int	fd_in;

	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
			return (-1);
	}
	fd_in = open(filename, O_RDONLY);
	return (fd_in);
}
