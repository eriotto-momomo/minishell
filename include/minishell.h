#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include "../lib/libft/libft.h"


/*			PROMPT			*/
void	prompt_loop(char *prompt);
char	*create_prompt(char **envp);
char	*join_prompt(char *usr, char *hostname);

#endif