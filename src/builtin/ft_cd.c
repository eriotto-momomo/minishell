/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/06 16:11:32 by timmi            ###   ########.fr       */
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

static char	*make_curpath(char *arg, char *pwd)
{
	char	*curpath;
	char	*temp;

	if (!arg || arg[0] == '~')
		return (ft_strdup(getenv("HOME")));
	if (arg[0] == '-')
		return (ft_strdup(getenv("OLDPWD")));
	if (arg[0] == '.' && arg[1] == '/')
	{
		arg++;
		if (pwd[ft_strlen(pwd)] == '/')
			return (ft_strjoin(pwd, arg));
		temp = ft_strjoin("/", arg);
		curpath = ft_strjoin(pwd, temp);
		free(temp);
		return (curpath);
	}
	return (ft_strdup(arg));
}

void	ft_replace(char **buff, char *new_value)
{
	if (buff || *buff)
	{
		w_free((void **)buff);
		*buff = NULL;
	}
	*buff = new_value;
}

int	ft_cd(t_shell *s)
{
	char	*arg;
	char	*curpath;

	arg = s->root_node->data.ast_exec.argv[1];
	curpath = make_curpath(arg, s->pwd);
	if (sizeof(curpath) > PATH_MAX)
		printf("curpath too long\n");
	ft_replace(&(s->old_pwd), save_cwd());
	if (chdir(curpath) == -1)
	{
		perror("cd");
		w_free((void **)&curpath);
		return (-1);
	}
	w_free((void **)&curpath);
	ft_replace(&(s->pwd), save_cwd());
	return (0);
}
