/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/16 12:57:35 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_input(t_shell *s)
{
	// 🚨 AJOUTER SAFE CHECKS
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
}

void prompt_loop(t_shell *s)
{
	static int i = 0;
	// 🚨 AJOUTER SAFE CHECKS
	while (1)
	{
		//printf("prompt_loop | while loop\n");

		if (s->sig_mode == DEFAULT_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
		}
		w_free((void **)&s->line);
		printf("%sprompt_loop | i: %d | s->line: %s%s\n", Y, i++, s->line, RST);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell s;

	(void)argv;
	// 🚨 AJOUTER SAFE CHECKS
	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		// debug(argv[1]);
	}
	else
	{
		init_shell(&s, envp);
		setup_signals(&s, MINISHELL_SIGNALS);
		create_prompt(&s);
		prompt_loop(&s);
	}
}
