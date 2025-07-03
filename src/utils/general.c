/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:34:21 by timmi             #+#    #+#             */
/*   Updated: 2025/07/03 10:32:14 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	v_switch(char **s, char *new_s)
{
	w_free((void **)s);
	*s = new_s;
}

size_t	count_var(t_env *head)
{
	size_t	count;

	count = 0;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

char	**ltotable(t_env *head)
{
	int		i;
	char	**env_table;
	char	*tmp;
	size_t	len;

	i = 0;
	len = count_var(head);
	env_table = malloc(sizeof(char *) * (len + 1));
	if (!env_table)
		return (NULL);
	while (head)
	{
		tmp = ft_str3join(head->name, "=", head->value);
		if (!tmp)
		{
			ft_free_char_array(env_table, len);
			return (NULL);
		}
		env_table[i++] = tmp;
		head = head->next;
	}
	env_table[i] = NULL;
	return (env_table);
}

int	perfect_match(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if ((ft_strlen(s1) == ft_strlen(s2))
		&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

int	f_close(int *fd)
{
	if (*fd > 2)
	{
		if (close(*fd) == -1)
			return (-1);
		*fd = -1;
	}
	return (0);
}
