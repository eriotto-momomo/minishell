/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:11:17 by timmi             #+#    #+#             */
/*   Updated: 2025/05/09 15:42:46 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char 	*get_var(char *s)
{
	char	*ret;
	int		start;
	int		i;
	
	start = 0;
	i = 0;
	while (s[start] && s[start] != '$')
		start++;
	i = start;
	while (s[i] && !ft_is_space(s[i]))
		i++;
	ret = malloc((i - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[start] && !ft_is_space(s[start]))
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

char	*expand(char *s, char *target, char *value)
{
	
}

void	var_expansion(t_shell *s, char *str)
{
	t_env	*ptr;
	char	*var;

	ptr = s->env_list;
	var = get_var(str);
	while (ptr)
	{
		if (ft_strncmp(var, ptr->name, ft_strlen(var)) == 0)
			
	}
}