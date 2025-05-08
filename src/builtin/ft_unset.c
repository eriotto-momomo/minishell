/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:19:19 by timmi             #+#    #+#             */
/*   Updated: 2025/05/08 17:20:57 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		delenv(t_shell *s, char *target)
{
	t_env	*temp;

	temp = s->env_list;
	while (temp)
	{
		if (ft_strncmp(target, temp->name, ft_strlen(target)) == 0)
		{
			del_var(&(s->env_list), &temp);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	ft_unset(t_shell *s)
{
	char	**args;
	int		i;
	
	if (s->root_node->data.ast_exec.argc == 1)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (0);
	}
	args = s->root_node->data.ast_exec.argv;
	i = 0;
	while (args[i])
		delenv(s, args[i++]);
	return (0);
}

