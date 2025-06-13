/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:13 by timmi             #+#    #+#             */
/*   Updated: 2025/06/13 11:13:57 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	replace_var(t_env **var, char *value)
{
	if (!value)
		return (0);
	w_free((void **)&(*var)->value);
	(*var)->value = value;
	return (1);
}

t_env	*var_lookup(t_env *env, char *target)
{
	t_env	*ptr;

	if (!target)
		return (NULL);
	ptr = env;
	while (ptr)
	{
		if (ft_strlen(ptr->name) == ft_strlen(target) &&
			ft_strncmp(ptr->name, target, ft_strlen(target)) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	exporter(t_env **env, char *arg)
{
	t_env	*var_ptr;
	char	*name;
	char	*value;

	name = get_name(arg);
	value = get_value(arg);
	var_ptr = var_lookup(*env, name);
	if (!var_ptr)
	{
		if (!add_var_back(env, name, value))
			return (0);
	}
	else
	{
		if (!replace_var(&var_ptr, value))
			return (0);
		free(name);
	}
	return (1);
}

static int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '=')
				return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_env **env, int ac, char **args, int fd)
{
	int		i;

	i = -1;
	if (ac == 1)
		ft_env(*env, fd);
	while (++i < ac)
	{
		printf("Evaluating :%s\n", args[i]);
		if (!is_valid(args[i]))
		{
			ft_putstr_fd("export: invalid identifier\n", 2);
			continue ;
		}
		if (!ft_strchr(args[i], '='))
			continue ;
		if (!exporter(env, args[i]))
			return (-1);
	}
	return (1);
}
