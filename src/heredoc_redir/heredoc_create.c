/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:07:12 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 12:29:18 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

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
	static int	index = 0;
	char		*file;

	file = create_file(eof_list[eof_count - 1], index);
	if (!file)
		return (NULL);
	s->tmp_files_list[index] = ft_strdup(file);
	if (!s->tmp_files_list[index])
	{
		w_free((void**)&file);
		ft_free_char_array(s->tmp_files_list, index - 1);
		ft_free_char_array(eof_list, eof_count);
		return (NULL);
	}
	index++;
	return (file);
}

int	create_heredoc(t_shell *s, char** eof_list, int eof_count)
{
	pid_t	heredoc_pid;
	int		tmp_file_fd;
	char	*tmp_file;

	tmp_file = create_tmp_file(s, eof_list, eof_count);
	if (!tmp_file)
		return (1);
	heredoc_pid = fork();
	if (heredoc_pid == 0)
	{
		setup_signals(s, DEFAULT_SIGNALS);
		write_heredoc(s, tmp_file, eof_list, eof_count);
		kill_children(s);
	}
	waitpid(heredoc_pid, NULL, 0);
	tmp_file_fd = open(tmp_file, O_RDONLY);
	if (tmp_file_fd < 0)
		return (print_error(&s->numerr, errno));
	return (tmp_file_fd);
}
