/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:20:28 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/25 15:12:18 by emonacho         ###   ########.fr       */
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
	ret = malloc((ft_strlen(name) + ft_strlen(value) + 3) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (name[++i])
		ret[i] = name[i];
	ret[i++] = '=';
	j = 0;
	while (value[j])
		ret[i++] = value[j++];
	ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

int	ft_env(t_shell *s, t_env *env, int fd_out)
{
	t_env	*ptr;
	char	*var;
	char	*tmp;
	char	*to_print;

	ptr = env;
	to_print = ft_strdup("");
	if (!to_print)
		return (print_error(&s->numerr, NULL, ENOMEM));
	while (ptr)
	{
		var = make_var(ptr->name, ptr->value);
		if (!var)
			return (print_error(&s->numerr, NULL, ENOMEM));
		tmp = to_print;
		to_print = ft_strjoin(to_print, var);
		free(var);
		free(tmp);
		if (!to_print)
			return (print_error(&s->numerr, NULL, ENOMEM));
		ptr = ptr->next;
	}
	ft_putstr_fd(to_print, fd_out);
	free(to_print);
	return (0);
}
