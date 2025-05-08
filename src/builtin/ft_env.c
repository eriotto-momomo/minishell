/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:20:28 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 14:30:11 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



static char	*make_var(char	*name, char *value)
{
	int		i;
	int		j;
	char	*ret;

	if (!name || !value)
		return (NULL);
	ret = malloc((ft_strlen(name) + ft_strlen(value) + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (name[++i])
		ret[i] = name[i];
	ret[i++] = '=';
	j = 0;
	while (value[j])
		ret[i++] = value[j++];
	ret[i] = '\0';
	return (ret);
}

void	ft_env(t_env *h_env, int fd_out)
{
	t_env	*ptr;
	char	*line;
	char	*temp;
	char	*to_print;

	ptr = h_env;
	to_print = ft_strdup("");
	while (ptr)
	{
		line = make_var(ptr->name, ptr->value);
		if (!line)
		{
			free (to_print);
			return ;
		}
		temp = ft_strjoin(to_print, line);
		free(line);
		free(to_print);
		to_print = ft_strjoin(temp, "\n");
		free(temp);
		ptr = ptr->next;
	}
	ft_putstr_fd(to_print, fd_out);
	free(to_print);
}
