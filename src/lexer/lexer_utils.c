/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/05/29 16:31:28 by timmi            ###   ########.fr       */
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

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
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
	word = malloc(sizeof(char) * len + 1);
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

char	*get_el(char *cmd)
{
	if (is_sep(*cmd))
		return (get_sep(cmd));
	return (get_word(cmd));
}
