/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/16 14:18:44 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_input(t_shell *s)
{
	lexer(s);
	if (parser(s))
		return ;
	free_ast(&(s->root_node));
}

void prompt_loop(t_shell *s)
{
	int loop;

	loop = 1;
	while (loop)
	{
		s->line = readline(s->prompt);
		if (s->line && *s->line) // need to add a check to not print strings containing only spaces
		{
			add_history(s->line);
			process_input(s);
		}	
		free(s->line);
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
