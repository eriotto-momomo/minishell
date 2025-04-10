/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/04/10 09:53:57 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_sep(char c)
{
	int	i;

	i = 0;
	while (SEPARATORS[i])
	{
		if (c == SEPARATORS[i])
			return (1);
		i++;
	}
	return (0);
}
char	*get_quote(char *cmd, int i)
{
	char	quote;
	char	*str;
	size_t	len;

	quote = cmd[i];
	len = 1;
	while (cmd[i + len] && cmd[i + len] != quote)
		len++;
	len++;
	str = malloc((sizeof(char) * len + 1));
	if (!str)
		return (NULL);
	len = 0;
	str[len++] = cmd[i++];
	while (cmd[i] && cmd[i] != quote)
		str[len++] = cmd[i++];
	str[len++] = cmd[i];
	str[len] = '\0';
	return (str);
}

char	*get_sep(char *cmd, int i)
{
	char	*sep;

	sep = malloc(sizeof(char) * 2);
	if (!sep)
		return (NULL);
	sep[0] = cmd[i];
	sep[1] = '\0';
	return (sep);
}

char	*get_word(char *cmd, int i)
{
	size_t	len;
	char	*word;

	len = 0;
	while (cmd[i + len] && !(is_sep(cmd[i + len]) || is_space(cmd[i + len])))
		len++;
	word = malloc((sizeof(char) * len) + 1);
	if (!word)
		return (NULL);
	len = 0;
	while (cmd[i] && !(is_sep(cmd[i]) || is_space(cmd[i])))
		word[len++] = cmd[i++];
	word[len] = '\0';
	return (word);
}