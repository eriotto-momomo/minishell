/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:04:01 by timmi             #+#    #+#             */
/*   Updated: 2025/04/25 19:11:45 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	in_pipe(int *p, t_ast *node)
{
	dup2(p[1], STDIN_FILENO);
	close(p[0]);
	close(p[1]);
	cmd_execution(node->data.ast_exec.argv);
}