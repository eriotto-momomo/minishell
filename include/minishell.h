/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:19:48 by timmi             #+#    #+#             */
/*   Updated: 2025/04/09 00:03:58 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include "../lib/libft/libft.h"

# define DEFAULT_PROMPT "minishell-1.0$ "

typedef struct	s_builtin
{
	char		*func_list;
}				t_builtin;

typedef struct	s_shell
{
	t_builtin	*builtins;
	char		**env;
}				t_shell;

/*			PROMPT			*/
void	prompt_loop(char *prompt, t_shell *s);
char	*create_prompt(void);

/*			PARSING?		*/
int	simple_token_interpreter(t_shell *s, char *line_read);

#endif