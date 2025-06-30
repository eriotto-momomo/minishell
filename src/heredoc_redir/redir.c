/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:23 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/30 09:02:03 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_heredoc(t_shell *s, t_ast **node, t_token **tok)
{
	// COMPTER LES HEREDOC POUR ALLOUER EOF_LIST
	(*node)->data.s_exec.eof_count = count_tokens(&(*tok), HERE_DOC);
	if ((*node)->data.s_exec.eof_count == 0)
		return (0);
	// COPIE LES EOF
	(*node)->data.s_exec.eof_list
		= copy_eof_list(*tok, (*node)->data.s_exec.eof_count);
	if (!(*node)->data.s_exec.eof_list)
		return (1);
	// ECRIRE LE HEREDOC
	(*node)->data.s_exec.fd_heredoc = create_heredoc(s, (*node)->data.s_exec.eof_list,
		(*node)->data.s_exec.eof_count);
	if ((*node)->data.s_exec.fd_heredoc < 0)
		return (1);
	return (0);
}

int	get_redir(t_shell *s, t_ast **node, t_token **tok)
{
	t_token	*tmp;

	(*node)->data.s_exec.fd_in = 0;
	(*node)->data.s_exec.fd_out = 1;
	tmp = *tok;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUT_REDIR || tmp->type == APP_OUT_REDIR)
			(*node)->data.s_exec.fd_out
				= redir_out(s, tmp->type, tmp->next->data,
					(*node)->data.s_exec.fd_out);
		else if (tmp->type == IN_REDIR)
			(*node)->data.s_exec.fd_in
				= redir_in(s, tmp->next->data, (*node)->data.s_exec.fd_in);
		if ((*node)->data.s_exec.fd_out < 0 || (*node)->data.s_exec.fd_in < 0)
		{
			(*node)->data.s_exec.fd_in = 0;
			(*node)->data.s_exec.fd_out = 1;
		}
		if (!get_next_token(&tmp))
			break ;
	}
	if (errno)
		ft_puterror(strerror(errno));
	return (0);
}

int	get_final_filename(t_shell *s, char **filename)
{
	if (expand(s->numerr, s->env_list, filename) != 0)
	{
		w_free((void **)&filename);
		return (print_error(&s->numerr, ENOMEM));
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

int	redir_out(t_shell *s, int mode, char *filename, int current_redir)
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
	if (mode == OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == APP_OUT_REDIR)
		fd_out = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	w_free((void **)&tmp);
	return (fd_out);
}

int	redir_in(t_shell *s, char *filename, int current_redir)
{
	int		fd_in;
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
