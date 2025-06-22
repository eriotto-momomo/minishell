/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/22 17:13:10 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_shell *s, int fd_out)
{
	char	*pwd;
	char	*tmp;

	pwd = ft_getenv(s->env_list, "PWD");
	if (!pwd)
	{
		pwd = s->pwd->value;
		if (!pwd)
			return (print_error(&s->numerr, ENOMEM, "ft_pwd"));
	}
	tmp = ft_strjoin(pwd, "\n");
	if (!tmp)
		return (print_error(&s->numerr, ENOMEM, "ft_pwd"));
	ft_putstr_fd(tmp, fd_out);
	free(tmp);
	return (0);
}
