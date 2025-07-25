/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:08:35 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/25 17:13:46 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_args(t_ast *node)
{
	char	**args;

	args = NULL;
	if (!node)
		return (NULL);
	if (node->tag == EXEC_NODE)
		args = node->data.s_exec.av;
	return (args);
}

static size_t	len_calc(int ac, char **tab)
{
	size_t	total_len;
	int		i;

	i = 1;
	total_len = 0;
	while (i < ac)
		total_len += ft_strlen(tab[i++]);
	return (total_len + ac - 1);
}

static char	*tab_to_string(int ac, char **tab, int offset)
{
	int		i;
	char	*ptr;
	char	*ret;
	size_t	len;

	i = offset;
	len = len_calc(ac, tab);
	if (offset)
		len++;
	ret = malloc(len);
	if (!ret)
		return (NULL);
	ptr = ret;
	while (++i < ac)
	{
		ft_memcpy(ptr, tab[i], ft_strlen(tab[i]));
		ptr += ft_strlen(tab[i]);
		if (i != ac - 1)
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

int	ft_echo(t_shell *s, t_ast **current_node, int fd_out)
{
	char	**args;
	char	*str;
	int		offset;

	offset = 0;
	args = get_args(*current_node);
	fprintf(stderr, "%d\n", fd_out);
	if (!args)
		return (print_error(&s->numerr, NULL, ENOMEM));
	if (args[1])
	{
		if (flag_check(args[1]))
			offset = 1;
		str = tab_to_string((*current_node)->data.s_exec.ac, args, offset);
		if (!str)
			return (print_error(&s->numerr, NULL, ENOMEM));
		ft_putstr_fd(str, fd_out);
		free(str);
	}
	if (!offset)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
