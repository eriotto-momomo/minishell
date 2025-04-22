/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:02:33 by c4v3d             #+#    #+#             */
/*   Updated: 2025/04/22 23:06:21 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_check(t_shell *shell)
{
	if (ft_strnprefix((*shell->head)->data, "exit", ft_strlen("exit")) && !(*shell->head)->prev)
		terminate_shell(shell);
}

void terminate_shell(t_shell *minishell)
{
	if (minishell->head)
	{
		free_list(*minishell->head);
		printf("Linked list freed !\n");
	}
	// if (minishell->root_node)
	// {
	// 	printf("AST freed !\n");
	// }
	printf("Exiting minishell !\nSee you next time !\n");
	exit(0);
}