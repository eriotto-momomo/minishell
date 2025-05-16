/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:00:59 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/15 14:55:00 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*w_readline(const char *prompt, t_shell *s)
{
	(void)s;
	char	*line_read;

	line_read = readline(prompt);
	printf("w_readline | %sline read!%s\n", P, RST);
	if (!line_read)
		return (NULL);
	return (line_read);
}
