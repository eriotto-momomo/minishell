/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/04/29 15:03:14 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void initialize_struct(t_shell *s, char **envp)
{
	s->env = envp;
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
		if (s->line && *s->line) // need to add a check to not print strings containing only spaces
		{
			add_history(s->line);
			lexer(s);
			if (syntax_analysis(s->head))
				s->root_node = build_ast(&s->head);
			// simple_cmd(s->root_node, s->env);
			ft_echo(s->root_node->data.ast_exec.argv, 1);
		}
		// (void)ast; // 💥TEST
		free(s->line);
	}
}

int main(int argc, char **argv, char **envp)
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
		initialize_struct(&s, envp);
		prompt_loop(prompt, &s);
		free(prompt);
	}
}
