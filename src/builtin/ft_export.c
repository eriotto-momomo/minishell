/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:13 by timmi             #+#    #+#             */
/*   Updated: 2025/06/05 12:18:38 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	treat_var(t_env *env, char *arg)
{
	char	*name;
	char	*value;
	t_env	*ptr;

	if (!ft_strchr(arg, '='))
		return ;
	name = get_name(arg);
	value = get_value(arg);
	ptr = env;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
		{
			w_free((void **)&(ptr->value));
			ptr->value = ft_strdup(value);
			return ;
		}
		ptr = ptr->next;
	}
	add_var_back(&env, name, value);
}

int	ft_export(t_shell *s)
{
	int		i;
	char	**args;

	if (s->root_node->data.exec.argc == 1)
		return (0);
	i = 1;
	args = s->root_node->data.exec.argv;
	while (args[i])
		treat_var(s->env_list, args[i++]);
	return (0);
}
