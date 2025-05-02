/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/02 14:11:41 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_check(t_shell *shell)
{
	if (ft_strnprefix(shell->head->data, "exit", ft_strlen("exit")))
		terminate_shell(shell);
}

void terminate_shell(t_shell *s)
{
	if (s->head)
		free_list(&(s->head));
	if (s->root_node)
		printf("AST freed !\n");
	free(s->pwd);
	s->pwd = NULL;
	free(s->old_pwd);
	s->old_pwd = NULL;
	printf("Exiting minishell !\nSee you next time !\n");
	exit(0);
}