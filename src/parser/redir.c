/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:23 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/25 12:17:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_final_filename(t_shell *s, char **filename)
{
	if (expand(s->numerr, s->env_list, filename) != 0)
	{
		w_free((void **)&filename);
		return(print_error(&s->numerr, ENOMEM));
	}
	if (*filename && (ft_strchr(*filename, '\'')
			|| ft_strchr(*filename, '\"')))
	{
		if (trim_quote(filename, 0, 0) != 0)
		{
			w_free((void **)&filename);
			return (print_error(&s->numerr, errno));
		}
	}
	return (0);
}

int	redir_out(t_shell *s, int redir_mode, char *filename, int current_redir)
{
	int		fd_out;
	char	*tmp;

	tmp = ft_strdup(filename);
	if (get_final_filename(s, &tmp) != 0)
		return (-1);
	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
			return (-1);
	}
	if (redir_mode == OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_mode == APP_OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	w_free((void **)&tmp);
	return (fd_out);
}

int	redir_in(t_shell *s, char *filename, int current_redir)
{
	int	fd_in;
	char	*tmp;

	tmp = ft_strdup(filename);
	if (get_final_filename(s, &tmp) != 0)
		return (-1);
	if (current_redir > 2)
	{
		if (close(current_redir) < 0)
			return (-1);
	}
	fd_in = open(tmp, O_RDONLY);
	w_free((void **)&tmp);
	return (fd_in);
}
