/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/18 15:28:04 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../include/minishell.h"

void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	execution(s);
}

void prompt_loop(t_shell *s)
{
	while (1)
	{
		s->line = readline(s->prompt);
		if (s->line && *s->line)
		{
			add_history(s->line);
			process_input(s);
		}
		w_free((void **)&s->line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell s;

	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		debug(argv[1]);
	}
	else
	{
		init_shell(&s, envp);
		create_prompt(&s);
		prompt_loop(&s);
	}
}
