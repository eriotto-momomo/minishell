/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:30 by timmi             #+#    #+#             */
/*   Updated: 2025/06/23 09:57:08 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_termios(t_shell *s)
{
	if (tcgetattr(STDIN_FILENO, &s->termios.old) == -1)
		return (print_error(&s->numerr, ENOMEM, "init_termios"));
	s->termios.new = s->termios.old;
	s->termios.new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &s->termios.new) == -1)
		return (print_error(&s->numerr, ENOMEM, "init_termios"));
	return (0);
}

int	init_shell(t_shell *s, char	**envp)
{
	g_sig = 0;
	if (init_termios(s) != 0)
		return (-1);
	s->env_list = table_to_ll(envp);
	if (!s->env_list)
		return (-1);
	s->heredoc_tmp = ft_strdup(HEREDOC_FILE_PATH);
	if (!s->heredoc_tmp)
		return (-1);
	s->ret_value = 0;
	s->pipe_count = 0;
	s->prompt = NULL;
	s->line = NULL;
	s->pwd = var_lookup(s->env_list, "PWD");
	s->old_pwd = var_lookup(s->env_list, "PWD");
	s->home = var_lookup(s->env_list, "HOME");
	s->pid_count = 0;
	s->head = NULL;
	s->root_node = NULL;
	s->current_node = NULL;
	s->numerr = 0;
	s->sig_mode = MINISHELL_SIGNALS;
	return (0);
}
