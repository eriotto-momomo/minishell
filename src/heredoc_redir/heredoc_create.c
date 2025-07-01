/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:07:12 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/01 14:14:11 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	unlink_tmp_files(char **tmp_files_list, int heredoc_count)
{
	int	i;

	i = 0;
	while (i < heredoc_count)
	{
		printf("%sunlink_tmp_files | about to UNLINK and free array[%d]: %s%s\n", C, i, tmp_files_list[i], RST);
		if (unlink(tmp_files_list[i]) != 0)
			return (1);
		i++;
	}
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

char	*create_tmp_file(t_shell *s, char** eof_list, int eof_count)
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
