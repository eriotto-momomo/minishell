/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/22 14:51:45 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_sig;

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp) == 0)
	{
		if (create_prompt(&shell) == -1)
		{
			print_error(&shell.numerr, ENOMEM, "create_prompt");
			terminate_shell(&shell);
		}
		prompt_loop(&shell);
	}
	else
	{
		print_error(&shell.numerr, ENOMEM, "init_shell");
		exit(shell.numerr);
	}
	return (0);
}
