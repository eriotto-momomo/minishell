#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*prompt;
	if (argc > 1)
	{
		printf("%s\n", argv[1]);
		prompt = create_prompt(envp);
		printf("%s\n", prompt);
		free(prompt);
	}
}