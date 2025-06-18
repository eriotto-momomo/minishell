/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 10:17:13 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset(t_shell *s)
{
	s->pipe_count = 0;
	s->pid_count = 0;
	w_free((void **)&s->line);
}

static void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
	reset(s);
}

static void prompt_loop(t_shell *s)
{
	while (1)
	{
		s->line = (readline(s->prompt));
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
		}
		reset(s);
	}
}

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
