/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/25 12:26:27 by timmi            ###   ########.fr       */
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
		return (print_error(&s->numerr, ENOMEM));
	tmp = ft_strjoin(pwd, "\n");
	if (!tmp)
		return (print_error(&s->numerr, ENOMEM));
	ft_putstr_fd(tmp, fd_out);
	free(tmp);
	return (0);
}
