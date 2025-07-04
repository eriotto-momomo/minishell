/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:13 by timmi             #+#    #+#             */
/*   Updated: 2025/07/04 10:43:51 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	replace_var(t_env **var, char *value)
{
	if (!value)
		return (1);
	w_free((void **)&(*var)->value);
	(*var)->value = value;
	return (0);
}

t_env	*var_lookup(t_env *env, char *target)
{
	t_env	*ptr;

	if (!target)
		return (NULL);
	ptr = env;
	while (ptr)
	{
		if (ft_strlen(ptr->name) == ft_strlen(target)
			&& ft_strncmp(ptr->name, target, ft_strlen(target)) == 0)
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
			return (1);
	}
	else
	{
		if (replace_var(&var_ptr, value) != 0)
			return (1);
		free(name);
	}
	return (0);
}

static int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '$')
			continue ;
		if (ft_isquote(s[i]))
			continue ;
		if (!ft_isalnum(s[i]) && s[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_shell *s, t_env **env, t_ast *node)
{
	int		i;
	char	**args;

	i = -1;
	args = node->data.s_exec.av;
	if (node->data.s_exec.ac == 1)
		ft_env(s, *env, node->data.s_exec.fd_out);
	while (++i < node->data.s_exec.ac)
	{
		if (!is_valid(args[i]) || ft_strncmp(args[i], "=", 2) == 0)
		{
			print_error(&s->numerr, EINVAL);
			continue ;
		}
		if (!ft_strchr(args[i], '='))
			continue ;
		if (exporter(env, args[i]) != 0)
			return (print_error(&s->numerr, ENOMEM));
	}
	return (s->numerr = 0);
}
