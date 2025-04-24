/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/04/24 14:19:47 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void initialize_struct(t_shell *s)
{
	s->env = NULL;
	s->cmd_count = 0;
	s->line = NULL;
	s->head = NULL;
	s->root_node = NULL;
}

void prompt_loop(char *prompt, t_shell *s)
{
	int loop;

	loop = 1;
	while (loop)
	{
		s->line = readline(prompt);
		if (s->line) // need to add a check to not print strings containing only spaces
		{
			add_history(s->line);
			lexer(s);
			print_list(s->head);
			syntax_analysis(s->head);
			printf("Found %ld command(s)\n", s->cmd_count);
			s->root_node = parse_tokens(&s->head);
			free_list(s->head);
		}
		// (void)ast; // 💥TEST
		free(s->line);
	}
}

int main(int argc, char **argv)
{
	t_shell s;
	char *prompt;
	
	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		debug(argv[1]);
	}
	else
	{
		prompt = create_prompt();
		initialize_struct(&s);
		prompt_loop(prompt, &s);
		free(prompt);
	}
}
