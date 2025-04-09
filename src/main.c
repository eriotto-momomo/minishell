#include "../include/minishell.h"

void	prompt_loop(char *prompt)
{
	char	*line_read;
	int		loop;
	t_list	*head;

	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		if (line_read && *line_read) //need to add a check to not print strings containing only spaces
		{
			add_history(line_read);
			head = cmd_splicing(line_read);
			free_list(head);
		}
		free(line_read);
	}
}

int main(int argc, char **argv)
{
	char	*prompt;
	(void) argv;
	(void) argc;
	prompt = create_prompt();
	prompt_loop(prompt);
	free(prompt);
}