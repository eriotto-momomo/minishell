/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/08 18:44:07 by timmi            ###   ########.fr       */
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

static char	*make_curpath(t_shell *s)
{
	char	*arg;
	char	*pwd;
	char	*curpath;
	char	*temp;

	arg = s->root_node->data.ast_exec.argv[1];
	pwd = s->pwd;
	if (!arg || arg[0] == '~')
		return (ft_strdup(ft_getenv(s->env_list, "HOME")));
	if (arg[0] == '-')
		return (ft_strdup(ft_getenv(s->env_list, "OLDPWD")));
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

int	ft_cd(t_shell *s)
{
	char	*old_pwd;
	char	*curpath;

	curpath = make_curpath(s);
	if (ft_strlen(curpath) > PATH_MAX)
	{
		ft_putstr_fd("curpath too long\n", 2);
		return (-1);
	}
	old_pwd = save_cwd();
	if (chdir(curpath) == -1)
	{
		perror("cd");
		w_free((void **)&curpath);
		w_free((void **)&old_pwd);
		return (-1);
	}
	w_free((void **)&curpath);
	w_free((void **)&old_pwd);
	return (0);
}
