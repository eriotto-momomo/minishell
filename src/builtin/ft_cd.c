/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/07/25 15:12:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*save_cwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
		return (NULL);
	return (ft_strdup(buffer));
}

static char	*make_curpath(t_shell *s, char *arg)
{
	char	*curpath;
	char	*temp;

	if (!arg || (arg[0] == '~' && !arg[1]))
		return (ft_strdup(s->home->value));
	if (arg[0] == '-' && !arg[1])
		return (ft_strdup(s->old_pwd->value));
	if (arg[0] == '.' && arg[1] == '/')
	{
		arg += 2;
		if (s->pwd->value[ft_strlen(s->pwd->value) - 1] == '/')
			return (ft_strjoin(s->pwd->value, arg));
		temp = ft_strjoin("/", arg);
		if (!temp)
			return (NULL);
		curpath = ft_strjoin(s->pwd->value, temp);
		free(temp);
		return (curpath);
	}
	return (ft_strdup(arg));
}

static int	updatepath(t_env **pwd, t_env **old_pwd, char *new_pwd)
{
	char	*tmp_old;
	char	*tmp_new;

	if (!pwd || !old_pwd || !*pwd || !*old_pwd || !(*pwd)->value || !new_pwd)
		return (1);
	if (ft_strcmp((*pwd)->value, new_pwd) != 0)
	{
		tmp_old = ft_strdup((*pwd)->value);
		if (!tmp_old)
			return (1);
		tmp_new = ft_strdup(new_pwd);
		if (!tmp_new)
		{
			free(tmp_old);
			return (1);
		}
		if ((*old_pwd)->value)
			w_free((void **)&(*old_pwd)->value);
		(*old_pwd)->value = tmp_old;
		w_free((void **)&(*pwd)->value);
		(*pwd)->value = tmp_new;
	}
	return (0);
}

int	ft_cd(t_shell *s, int ac, char **av)
{
	char	*curpath;
	char	*new_pwd;

	if (ac > 2)
		return (print_error(&s->numerr, NULL, E2BIG));
	curpath = make_curpath(s, av[1]);
	if (!curpath)
		return (print_error(&s->numerr, NULL, ENOMEM));
	if (chdir(curpath) == -1)
	{
		free(curpath);
		return (print_custom_error(&s->numerr, 1, strerror(errno)));
	}
	w_free((void **)&curpath);
	new_pwd = save_cwd();
	if (!new_pwd)
		return (1);
	if (updatepath(&s->pwd, &s->old_pwd, new_pwd) != 0)
	{
		w_free((void **)&new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}
