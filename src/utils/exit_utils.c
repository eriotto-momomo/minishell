/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/02 15:56:21 by emonacho         ###   ########.fr       */
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
		free_ast(&(s->root_node));
	w_free((void **)&(s->pwd));
	w_free((void **)&(s->old_pwd));
	w_free((void **)&(s->prompt));
	printf("Exiting minishell !\nSee you next time !\n");
	exit(0);
}
