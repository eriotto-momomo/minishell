/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/06/19 13:27:11 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_status = EXIT_READY;

// 🚨 AJOUTER SAFE CHECKS ???
void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
}

// 🚨 AJOUTER SAFE CHECKS ???
void prompt_loop(t_shell *s)
{
	//static int i = 0;

	while (1)
	{
		if (s->sig_mode == DEFAULT_SIGNALS)
			setup_signals(s, MINISHELL_SIGNALS);
		s->line = (readline(s->prompt));
		if (s->line == NULL)
			terminate_shell(s, 0);
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
		}
		w_free((void **)&s->line);
		//printf("%sprompt_loop | i: %d | s->line: %s%s\n", Y, i++, s->line, RST);	// 🖨️PRINT💥DEBUGING
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
		setup_signals(&s, MINISHELL_SIGNALS);
		create_prompt(&s);
		prompt_loop(&s);
	}
}
