/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/25 16:07:30 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_shell *s, int fd_out)
{
	char	*pwd;
	char	buff[PATH_MAX];
	char	*tmp;

	pwd = getcwd(buff, PATH_MAX);
	if (!pwd)
		return (print_error(&s->numerr, NULL, ENOMEM));
	tmp = ft_strjoin(pwd, "\n");
	if (!tmp)
		return (print_error(&s->numerr, NULL, ENOMEM));
	ft_putstr_fd(tmp, fd_out);
	free(tmp);
	return (s->numerr = 0);
}
