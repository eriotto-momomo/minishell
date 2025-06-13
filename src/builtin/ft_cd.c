/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/06/13 11:46:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*save_cwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("getwcd failed: ");
		return (NULL);
	}
	return (ft_strdup(buffer));
}

static char	*make_curpath(char *pwd, char *oldpwd, char *home, char *arg)
{
	char	*curpath;
	char	*temp;

	if (!arg || (arg[0] == '~' && !arg[1]))
		return (ft_strdup(home));
	if ((arg[0] == '-' && !arg[1]))
		return (ft_strdup(oldpwd));
	if (arg[0] == '.' && arg[1] == '/')
	{
		arg += 2;
		if (pwd[ft_strlen(pwd)] == '/')
			return (ft_strjoin(pwd, arg));
		temp = ft_strjoin("/", arg);
		curpath = ft_strjoin(pwd, temp);
		free(temp);
		return (curpath);
	}
	return (ft_strdup(arg));
}

static int	replace_path(t_env **pwd, t_env **oldpwd, char *tmp)
{
	w_free((void **)&(*pwd)->value);
	(*pwd)->value = save_cwd();
	if (!*pwd)
		return (0);
	w_free((void **)&(*oldpwd)->value);
	(*oldpwd)->value = tmp;
	return (1);
}

int	ft_cd(t_env *pwd, t_env *oldpwd, t_env *home, t_ast *node)
{
	(void)node;
	char	*curpath;
	char	*tmp;

	if (node->data.exec.argc > 2)
		ft_putstr_fd("To many arguments\n", 2);
	curpath = make_curpath(home->value, oldpwd->value, pwd->value, node->data.exec.argv[1]);
	if (!curpath)
		return (1);
	tmp = pwd->value;
	if (chdir(curpath) == -1)
	{
		perror("cd :");
		free(curpath);
		return (-1);
	}
	free(curpath);
	if (!replace_path(&pwd, &oldpwd, tmp))
		return (1);
	return (0);
}
