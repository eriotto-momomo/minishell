/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/24 16:29:42 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*get_quote(char *cmd)
{
	char	quote;
	char	*str;
	size_t	len;
	size_t	i;

	if (!cmd || (*cmd != '\'' && *cmd != '"'))
		return (NULL);
	quote = *cmd;
	len = 1;
	while (cmd[len] && cmd[len] != quote)
		len++;
	if (!cmd[len])
		return (NULL);
	len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = cmd[i];
	str[i] = '\0';
	return (str);
}

char	*get_sep(char *cmd)
{
	char	*sep;

	if (!cmd)
		return (NULL);
	if ((cmd[0] == '<' && cmd[1] == '<') || (cmd[0] == '>' && cmd[1] == '>'))
	{
		sep = malloc(3);
		if (!sep)
			return (NULL);
		sep[0] = cmd[0];
		sep[1] = cmd[1];
		sep[2] = '\0';
	}
	else
	{
		sep = malloc(2);
		if (!sep)
			return (NULL);
		sep[0] = cmd[0];
		sep[1] = '\0';
	}
	return (sep);
}


char	*get_word(char *cmd)
{
	size_t	len;
	char	*word;
	size_t	i;

	if (!cmd)
		return (NULL);
	len = 0;
	while (cmd[len] && !is_sep(cmd[len]) && !ft_isspace(cmd[len]))
		len++;

	word = malloc(len + 1);
	if (!word)
		return (NULL);

	i = 0;
	while (i < len)
	{
		word[i] = cmd[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}


