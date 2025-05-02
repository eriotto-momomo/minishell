/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:03:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/02 15:48:35 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	trim_prompt(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[start] != '/')
		start++;
	while (str[end] != '.' && str[end] != ':')
		end++;
	str[end] = '\0';
	ft_memmove(str, str + start + 1, end);
}

static char	*join_prompt(char *usr, char *hostname)
{
	char	*full_prompt;

	usr = ft_strjoin(usr, "@");
	hostname = ft_strjoin(hostname, ": ");
	full_prompt = ft_strjoin(usr, hostname);
	free(usr);
	free(hostname);
	return (full_prompt);
}

char	*create_prompt(void)
{
	char	*usr;
	char	*host_name;
	char	*full_prompt;

	usr = getenv("USER");
	host_name = getenv("HOSTNAME");
	if (!host_name)
	{
		host_name = getenv("SESSION_MANAGER");
		if (host_name)
			trim_prompt(host_name);
	}
	if (usr && host_name)
		full_prompt = join_prompt(usr, host_name);
	else
		full_prompt = ft_strdup(DEFAULT_PROMPT);
	return (full_prompt);
}
