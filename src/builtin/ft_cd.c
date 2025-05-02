/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:59:30 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/02 12:00:20 by timmi            ###   ########.fr       */
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
	return(ft_strdup(buffer));
}

static char	*make_curpath(char *arg, char *pwd)
{
	// char	*temp;
	
	if (!arg)
		return (getenv("HOME"));
	if (arg[0] == '.')
	{
		arg++;
		if (pwd[ft_strlen(pwd)] == '/')
			return (ft_strjoin(pwd, arg));
		// temp = arg;
		arg = ft_strjoin("/", arg);
		// free(temp);
		return (ft_strjoin(pwd, arg));
	}
	return (arg);
}

int	ft_cd(t_shell *s)
{
	char	*arg;
	char	*curpath;

	arg = s->root_node->data.ast_exec.argv[1];
	
	s->old_pwd = s->pwd; // TO INIT
	
	curpath = make_curpath(arg, s->pwd);
	if (sizeof(curpath) > PATH_MAX)
		printf("curpath too long\n");
	printf("curpath : %s\n", curpath);
	if (chdir(curpath) == -1)
	{
		perror("cd");
		return (-1);
	}
	s->pwd = save_cwd();
	printf("pwd : %s\n", s->pwd);
	return(0);
}