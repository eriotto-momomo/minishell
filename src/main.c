/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/04/10 13:41:14 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_list(t_list *head)
{
	t_list	*temp;

	temp = head;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
}

void	initialize_struct(t_shell *s)
{
	(void)s;
}

void	prompt_loop(char *prompt, t_shell *s)
{
	char	*line_read;
	int		loop;
	t_list	*head;

	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		simple_token_interpreter(s, line_read);
		if (line_read && *line_read)
		// need to add a check to not print strings containing only spaces
		{
			add_history(line_read);
			head = tokenize(line_read);
			print_list(head);
			free_list(head);
		}
		free(line_read);
	}
}

int	main(int argc, char **argv)
{
	t_shell	s;
	char	*prompt;

	(void)argv;
	(void)argc;
	prompt = create_prompt();
	prompt_loop(prompt, &s);
	free(prompt);
}
