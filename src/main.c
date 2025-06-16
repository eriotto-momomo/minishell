/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 16:51:43 by timmi            ###   ########.fr       */
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

	(void)argv;
	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		// debug(argv[1]);
	}
	else
	{
		init_shell(&s, envp);
		create_prompt(&s);
		prompt_loop(&s);
	}
}
