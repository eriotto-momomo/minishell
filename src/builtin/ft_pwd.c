/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:13:49 by timmi             #+#    #+#             */
/*   Updated: 2025/05/09 13:40:16 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_shell *s, int	fd_out)
{
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
	{
		pwd = s->pwd;
		if (!pwd)
			return (-1);
	}
	ft_putstr_fd(pwd, fd_out);
	return (0);
}
