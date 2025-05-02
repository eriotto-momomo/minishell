/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/02 10:45:30 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printPreorder(t_ast *node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	if (node->tag == AST_PIPE)
		printf("|\n");
	else if (node->tag == AST_REDIR)
		printf(">\n");
	else if (node->tag == AST_EXEC)
		printf("%s\n", node->data.ast_exec.argv[0]);

	if (node->tag != AST_EXEC)
	{
		printPreorder(node->data.ast_pipe.right);
		printPreorder(node->data.ast_pipe.left);
	}
	else
		return;
}

void initialize_struct(t_shell *s, char **envp)
{
	s->env = envp;
	s->cmd_count = 0;
	s->line = NULL;
	s->old_path = NULL;
	s->head = NULL;
	s->root_node = NULL;
}

void prompt_loop(char *prompt, t_shell *s)
{
	int loop;
	t_list	*tok;

	loop = 1;
	while (loop)
	{
		s->line = readline(prompt);
		if (s->line && *s->line) // need to add a check to not print strings containing only spaces
		{
			add_history(s->line);
			lexer(s);
			tok = s->head;
			if (syntax_analysis(s->head))
				s->root_node = build_ast(&tok);
			//simple_cmd(s->root_node, s->env);
			//printPreorder(s->root_node);
		}
		free_list(s->head);
		// (void)ast; // 💥TEST
		free(s->line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell s;
	char *prompt;

	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		debug(argv[1]);
	}
	else
	{
		prompt = create_prompt();
		initialize_struct(&s, envp);
		prompt_loop(prompt, &s);
		free(prompt);
	}
}
