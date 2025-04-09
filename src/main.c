#include "../include/minishell.h"

void	initialize_struct(t_shell *s)
{
	w_malloc((void **)&s->builtins->func_list, 40);
	s->builtins->func_list[40 - 1] = '\0';
	s->builtins->func_list = "cd echo env exit export pwd unset";
}

void	prompt_loop(char *prompt, t_shell *s)
{
	char	*line_read;
	int		loop;

	loop = 1;
	while (loop)
	{
		line_read = readline(prompt);
		simple_token_interpreter(s, line_read);
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
	t_shell		s;
	char	*prompt;

	initialize_struct(&s);
	if (argc > 1)
	{
		if (argv[1])
		{
			prompt = create_prompt();
			prompt_loop(prompt, &s);
			//free(s.builtins.func_list);
			free(prompt);
		}
	}
}