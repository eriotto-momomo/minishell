/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/09 17:40:35 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void initialize_struct(t_shell *s, char	**envp)
{
	s->env = envp;
	s->prompt = NULL;
	s->cmd_count = 0;
	s->line = NULL;
	s->old_pwd = NULL;
	s->pwd = save_cwd();
	s->old_pwd = save_cwd();
	s->head = NULL;
	s->root_node = NULL;
	s->sig = malloc(sizeof(t_sig *));
}


void prompt_loop(t_shell *s)
{
	sig_setup();
	while (1)
	{
		//s->line = w_readline(s->prompt, s); //🚩 test
		s->line = readline(s->prompt);
		if (s->line && *s->line) // need to add a check to not print strings containing only spaces
		{
			add_history(s->line);
			lexer(s);
			parser(s);
			//simple_cmd(s->root_node, s->env);
			//ft_cd(s);
			free_ast(&(s->root_node));
			free_list(&(s->head));
		}
		free(s->line);
	}
	free(s->sig);
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
		initialize_struct(&s, envp);
		s.prompt = create_prompt();
		prompt_loop(&s);
	}
}
