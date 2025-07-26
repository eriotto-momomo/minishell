/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:19:19 by timmi             #+#    #+#             */
/*   Updated: 2025/07/22 16:49:58 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shell *s, int ac, char **av)
{
	int		i;
	t_env	*tmp;

	if (s->current_node->data.s_exec.fd_in != STDIN_FILENO)
		return (0);
	if (ac == 1)
		return (0);
	i = 1;
	while (i < ac)
	{
		tmp = var_lookup(s->env_list, av[i]);
		if (tmp)
			del_var(&s->env_list, &tmp);
		i++;
	}
	return (s->numerr = 0);
}
