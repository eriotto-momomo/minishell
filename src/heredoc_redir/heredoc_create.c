/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:07:12 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/27 10:52:39 by emonacho         ###   ########.fr       */
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


int	create_heredoc(t_shell *s, char** eof_list, int eof_count)
{
	(void)s;
	static int	index = 0;
	int			fd;
	char		*file;

	//s->tmp_files_list = create_tmp_file_list();
	file = create_file(eof_list[eof_count - 1], index++);
	if (!file)
		return (1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		w_free((void**)&file);
		return (1);
	}

	return (1);
	return (0);
}
