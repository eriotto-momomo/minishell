/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:07:12 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 19:55:06 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	unlink_tmp_files(char **tmp_files_list, int heredoc_count)
{
	int	i;

	i = 0;
	while (i < heredoc_count)
	{
		printf("%sunlink_tmp_files | about to UNLINK array[%d]: %s%s\n", C, i, tmp_files_list[i], RST);
		if (unlink(tmp_files_list[i]) != 0)
			return (1);
		//w_free((void**)&tmp_files_list[i]);
		i++;
	}
	//w_free((void**)&tmp_files_list);
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
		g_sig = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		//setup_signals(s, HEREDOC_SIGNALS);
		if (write_heredoc(s, path, eof_list, eof_count) != 0)
		{
			ft_free_char_array(eof_list, eof_count);
			w_free((void**)&path);
			return (-1);
			// exit(-1); en cas de probleme?
		}
		//kill_children(s);
		exit(0);
	}
	waitpid(heredoc_pid, NULL, 0);
	setup_signals(s, DEFAULT_SIGNALS);
	fprintf(stderr, "%sfork_heredoc | EXIT FUNCTION!%s\n", G, RST);
	return (0);
}

static char	*create_path(char *eof, int index)
{
	char	*file;
	char	*str_index;
	char	*tmp;

	str_index = ft_itoa(index);
	if (!str_index)
		return (NULL);
	file = ft_str3join(".", str_index, eof);
	if (!file)
	{
		w_free((void **)&str_index);
		return (NULL);
	}
	w_free((void **)&str_index);
	tmp = ft_strjoin("./tmp/", file);
	if (!tmp)
	{
		w_free((void **)&file);
		return (NULL);
	}
	w_free((void **)&file);
	printf("%screate_path | HEREDOC PATH: %s%s\n", C, tmp, RST);
	return (tmp);
}

static char	*create_tmp_file(t_shell *s, char** eof_list, int eof_count)
{
	s->tmp_index++;
	s->tmp_files_list[s->tmp_index] = create_path(eof_list[eof_count - 1], s->tmp_index);
	if (!s->tmp_files_list[s->tmp_index])
	{
		ft_free_char_array(s->tmp_files_list, s->heredoc_count);
		ft_free_char_array(eof_list, eof_count);
		return (NULL);
	}
	return (s->tmp_files_list[s->tmp_index]);
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
		print_error(&s->numerr, errno);
		return (-1);
	}
	return (tmp_file_fd);
}
