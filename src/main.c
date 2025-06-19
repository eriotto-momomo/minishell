/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 11:34:38 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp) == 0)
	{
		if (create_prompt(&shell) == -1)
			terminate_shell(&shell, 1);
		prompt_loop(&shell);
	}
	else
	{
		perror("Initialization failed !");
		exit(1);
	}
	return (0);
}
