/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:03:18 by timmi             #+#    #+#             */
/*   Updated: 2025/04/03 17:20:16 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_variable(char *target, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], target, ft_strlen(target)) == 0)
			i++;
		else
			return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

static char	*trim_prompt(char *str)
{
	char	*new_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*str != '/')
		str++;
	str++;
	while (!(str[i] == '.' || str[i] == ':'))
    {
        i++;
		count++;
    }
	new_str = malloc((sizeof(char) * count) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (!(str[i] == '.' || str[i] == ':'))
	{
		new_str[i] = str[i];
        i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*join_prompt(char *usr, char *hostname)
{
	char	*full_prompt;

	usr = ft_strjoin(usr, "@");
	hostname = ft_strjoin(hostname, ": ");
	full_prompt = ft_strjoin(usr, hostname);
	free(usr);
	free(hostname);
	return (full_prompt);
}

char	*create_prompt(char **envp)
{
	char	*usr;
	char	*host_name;
	char	*temp;
	char	*full_prompt;

	usr = get_variable("USER", envp);
	host_name = get_variable("HOSTNAME", envp);
	temp = NULL;
	if (!host_name)
	{
		host_name = get_variable("SESSION_MANAGER", envp);
		host_name = trim_prompt(host_name);
		temp = host_name;
	}
	full_prompt = join_prompt(usr, host_name);
	if (temp)
		free(temp);
	return (full_prompt);
}
