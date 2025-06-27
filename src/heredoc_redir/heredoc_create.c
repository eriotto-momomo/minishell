/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:07:12 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:07 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	unlink_tmp_files(char **tmp_files_list, int heredoc_count)
{
	int	i;

	i = 0;
	while (i < heredoc_count)
	{
		if (unlink(tmp_files_list[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	fork_heredoc(t_shell *s, char *path, char** eof_list, int eof_count)
{
	pid_t	heredoc_pid;

	heredoc_pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_pid == 0)
	{
		setup_signals(s, DEFAULT_SIGNALS);
		if (write_heredoc(s, path, eof_list, eof_count) != 0)
		{
			ft_free_char_array(eof_list, eof_count);
			w_free((void**)&path);
			return (-1);
			// exit(-1); en cas de probleme?
		}
		kill_children(s);
	}
	waitpid(heredoc_pid, NULL, 0);
	setup_signals(s, DEFAULT_SIGNALS);
	return (0);
}

static char	*create_file(char *eof, int index)
{
	char	*file;

	file = ft_str3join(".", ft_itoa(index), eof);
	if (!file)
		return (NULL);
	file = ft_strjoin("./tmp/", file);
	if (!file)
		return (NULL);
	printf("%screate_file | HEREDOC PATH: %s%s\n", C, file, RST);
	return (file);
}


static char	*create_tmp_file(t_shell *s, char** eof_list, int eof_count)
{
	char		*file;

	file = create_file(eof_list[eof_count - 1], s->tmp_index);
	if (!file)
	{
		ft_free_char_array(eof_list, eof_count);
		return (NULL);
	}
	s->tmp_files_list[s->tmp_index] = ft_strdup(file);
	if (!s->tmp_files_list[s->tmp_index])
	{
		w_free((void**)&file);
		ft_free_char_array(s->tmp_files_list, s->tmp_index - 1);
		ft_free_char_array(eof_list, eof_count);
		return (NULL);
	}
	s->tmp_index++;
	return (file);
}


int	create_heredoc(t_shell *s, char** eof_list, int eof_count)
{
	int		tmp_file_fd;
	char	*tmp_file;

	tmp_file = create_tmp_file(s, eof_list, eof_count);
	if (!tmp_file)
		return (-1);
	if (fork_heredoc(s, tmp_file, eof_list, eof_count) != 0)
		return (-1);
	tmp_file_fd = open(tmp_file, O_RDONLY);
	if (tmp_file_fd < 0)
	{
		ft_free_char_array(s->tmp_files_list, s->heredoc_count);
		ft_free_char_array(eof_list, eof_count);
		w_free((void**)&tmp_file);
		print_error(&s->numerr, errno);
		return (-1);
	}
	w_free((void**)&tmp_file);
	return (tmp_file_fd);
}
