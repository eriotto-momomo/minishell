/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:08:35 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 21:19:13 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	len_calc(char **tab)
{
	size_t	total_len;
	int		i;

	i = 1;
	total_len = 0;
	while (tab[i])
	{
		total_len += ft_strlen(tab[i]);
		if (tab[i + 1])
			total_len += 1;
		i++;
	}
	return (total_len);
}

static char	*tab_to_string(char **tab, int i)
{
	char	*ptr;
	char	*ret;
	size_t	len;

	ret = NULL;
	len = len_calc(tab);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ptr = ret;
	while (tab[++i])
	{
		ft_memcpy(ptr, tab[i], ft_strlen(tab[i]));
		ptr += ft_strlen(tab[i]);
		if (tab[i + 1])
		{
			*ptr = ' ';
			ptr++;
		}
	}
	*ptr = '\0';
	return (ret);
}

static int	flag_check(char *flag)
{
	int	i;

	if (flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_shell *s, int fd_out)
{
	char	**args;
	char	*temp;
	char	*str;
	int		offset;

	offset = 0;
	args = s->root_node->data.ast_exec.argv;
	if (args[1])
	{
		if (flag_check(args[1]))
			offset = 1;
		str = tab_to_string(args, offset);
		if (!str)
			return (-1);
		if (!offset)
		{
			temp = str;
			str = ft_strjoin(str, "\n");
			free(temp);
			temp = NULL;
		}
		write(fd_out, str, ft_strlen(str));
		free(str);
	}
	return (0);
}
