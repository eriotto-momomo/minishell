/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/13 21:14:10 by c4v3d            ###   ########.fr       */
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
