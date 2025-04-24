/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/04/21 14:31:44 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize_struct(t_shell *s)
{
	(void)s;
}

void	prompt_loop(char *prompt, t_shell *s)
{
	char	*line_read;
	int		loop;
	t_list	*head;
	t_ast	*ast;

	(void) s;
	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		if (line_read && *line_read)
		// need to add a check to not print strings containing only spaces
		{
			add_history(line_read);
			head = tokenize(line_read);
			print_list(head);
			ast = build_ast(&head);
			free_list(head);
			// free_ast(ast) // TO DO👷‍♂️
		}
		(void)ast; // 💥TEST
		free(line_read);
	}
}

int	main(int argc, char **argv)
{
	t_shell	s;
	char	*prompt;

	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		debug(argv[1]);
	}
	else
	{
		prompt = create_prompt();
		prompt_loop(prompt, &s);
		free(prompt);
	}
}
