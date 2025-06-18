/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/18 09:34:49 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset(t_shell *s)
{
	s->pipe_count = 0;
	s->pid_count = 0;
	w_free((void **)&s->line);
}

void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
	reset(s);
}

void prompt_loop(t_shell *s)
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
	t_shell s;

	(void)argc;
	(void)argv;
	if (init_shell(&s, envp) == 0)
	{
		if (create_prompt(&s) == -1)
			terminate_shell(&s, 1);
		prompt_loop(&s);
	}
	else
	{
		perror("Something went wrong at startup.");
		exit(1);
	}
}
