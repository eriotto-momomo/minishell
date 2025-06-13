/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:45:19 by timmi             #+#    #+#             */
/*   Updated: 2025/05/29 16:32:11 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_quote(char **s)
{
	char	*trimmed;
	char	*str;
	size_t	len;

	str = *s;
	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
	{
		trimmed = ft_substr(str, 1, len - 2);
		if (!trimmed)
			return (0);
		free(*s);
		*s = trimmed;
	}
	return (1);
}
