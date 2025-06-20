/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/20 10:21:44 by timmi            ###   ########.fr       */
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
	if ((arg[0] == '-' && !arg[1]))
		return (ft_strdup(s->old_pwd->value));
	if (arg[0] == '.' && arg[1] == '/')
	{
		arg += 2;
		if (s->pwd->value[ft_strlen(s->pwd->value)] == '/')
			return (ft_strjoin(s->pwd->value, arg));
		temp = ft_strjoin("/", arg);
		curpath = ft_strjoin(s->pwd->value, temp);
		free(temp);
		return (curpath);
	}
	return (ft_strdup(arg));
}

static int	updatepath(t_shell *s)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = ft_strdup(s->pwd->value);
	if (!old_pwd)
		return (print_error(&s->numerr, errno, "ft_strdup"));
	new_pwd = save_cwd();
	if (!new_pwd)
	{
		free(old_pwd);
		return (print_error(&s->numerr, errno, "save_cwd"));
	}
	if (!replace_var(&s->old_pwd, old_pwd))
	{
		free(new_pwd);
		return (print_error(&s->numerr, ENOMEM, "save_cwd"));
	}
	if (!replace_var(&s->pwd, new_pwd))
		return (print_error(&s->numerr, ENOMEM, "save_cwd"));
	return (0);
}

int	ft_cd(t_shell *s, int ac, char **av)
{
	char	*curpath;

	if (ac > 2)
		return (print_error(&s->numerr, E2BIG, "cd"));
	curpath = make_curpath(s, av[1]);
	if (!curpath)
		return (print_error(&s->numerr, ENOMEM, "cd"));
	if (chdir(curpath) == -1)
	{
		free(curpath);
		return (print_error(&s->numerr, errno, "cd"));
	}
	free(curpath);
	updatepath(s);
	return (0);
}
