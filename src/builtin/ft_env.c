/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:20:28 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 13:44:59 by timmi            ###   ########.fr       */
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
	char	*var;
	char	*temp;
	char	*to_print;

	ptr = h_env;
	to_print = ft_calloc(1, 1);
	while (ptr)
	{
		var = make_var(ptr->name, ptr->value);
		temp = ft_strjoin(to_print, var);
		free(var);
		free(to_print);
		to_print = ft_strjoin(temp, "\n");
		free(temp);
		ptr = ptr->next;
	}
	ft_putstr_fd(to_print, fd_out);
}
