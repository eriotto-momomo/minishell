#include "../include/minishell.h"

void	prompt_loop(char *prompt)
{
	char	*line_read;
	int		loop;

	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		if (line_read && *line_read) //need to add a check to not print strings containing only spaces
		{
			add_history(line_read);
			printf("%s\n", line_read);
		}
		free(line_read);
	}
}

int main(int argc, char **argv)
{
	char	*prompt;
	if (argc > 1)
	{
		if (argv[1])
		{
			prompt = create_prompt();
			prompt_loop(prompt);
			free(prompt);
		}
	}
}