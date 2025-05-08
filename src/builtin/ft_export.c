/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:13 by timmi             #+#    #+#             */
/*   Updated: 2025/05/08 18:54:22 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	treat_var(t_env *env, char *arg)
{
	char	*name;
	char	*value;
	t_env	*ptr;
	
	if (ft_strchr(arg, '='))
		return ;
	name = get_name(arg);
	value = get_name(arg);
	ptr = env;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
		{
			w_free((void **)&(ptr->value));
			ptr->name = value;
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

	if (s->root_node->data.ast_exec.argc == 1)
		return (0);
	args = s->root_node->data.ast_exec.argv;
	while (args[i])
		treat_var(s->env_list, args[i++]);
	return (0);
}
