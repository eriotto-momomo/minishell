/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:23 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 20:36:30 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_out(int redir_mode, char *filename, int current_redir)
{
	int		fd_out;
	char	*tmp;

	tmp = ft_strdup(filename);
	if (!tmp)
		return (-1);
	if (trim_quote(&tmp, 0, 0) != 0)
	{
		w_free((void **)tmp);
		return (-1);
	}
	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
		{
			w_free((void **)tmp);
			return (-1);
		}
	}
	if (redir_mode == OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_mode == APP_OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	w_free((void **)tmp);
	return (fd_out);
}

int	redir_in(char *filename, int current_redir)
{
	int	fd_in;
	char	*tmp;

	tmp = ft_strdup(filename);
	if (!tmp)
		return (-1);
	if (trim_quote(&tmp, 0, 0) != 0)
	{
		w_free((void **)&tmp);
		return (-1);
	}
	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
		{
			w_free((void **)&tmp);
			return (-1);
		}
	}
	fd_in = open(tmp, O_RDONLY);
	w_free((void **)&tmp);
	return (fd_in);
}
