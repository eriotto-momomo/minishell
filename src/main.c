#include "../include/minishell.h"

void	prompt_loop(char *prompt)
{
	char	*line_read;
	int		loop;

	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		if (line_read && *line_read)
		{
			add_history(line_read);
			printf("%s\n", line_read);
		}
		free(line_read);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*prompt;
	if (argc > 1)
	{
		if (argv[1])
		{
			prompt = create_prompt(envp);
			prompt_loop(prompt);
		}
	}
}