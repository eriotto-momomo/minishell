/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/17 17:15:01 by timmi            ###   ########.fr       */
=======
/*   Updated: 2025/04/20 22:04:17 by emonacho         ###   ########.fr       */
>>>>>>> main
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
			head = lexer(line_read);
			syntax_analysis(head);
			print_list(head);
			ast = parse_tokens(&head);
			free_list(head);
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
