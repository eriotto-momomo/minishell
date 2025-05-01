/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/01 17:42:05 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*save_cwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("getwcd failed: ");
		return (NULL);
	}
	return(ft_strdup(buffer));
}

static char	*make_path(char *arg, char *pwd)
{
	char	*home;
	//char	*path;
	
	if (!arg)
	{
		home = getenv("HOME");
		if (!home)
			return (NULL);
		return (home);
		
	}
	if (ft_strnstr(arg, "..", 2) || arg[0] == '.')
		printf("found\n");
	else
	{
		if (pwd[ft_strlen(pwd)] != '/')
			return  (ft_strjoin(pwd, arg));
		arg++;
		printf("trim!\n");
		return  (ft_strjoin(pwd, arg));
	}
	return (NULL);
}

int	ft_cd(t_shell *s)
{
	char	*arg;
	char	*path;

	arg = s->root_node->data.ast_exec.argv[1];
	s->old_path = save_cwd();
	if (!s->old_path)
		return (1);
	path = make_path(arg, s->old_path);
	if (sizeof(path) > PATH_MAX)
		printf("Path too long\n");
	printf("path :%s\n", path);
	chdir(path);
	printf("pwd :%s\n", getenv("PWD"));
	return(0);
}