/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by timmi             #+#    #+#             */
/*   Updated: 2025/05/15 18:17:25 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../include/minishell.h"

// static void	print_ast(t_ast *current_node)
// {
// 	if (!current_node)
// 		return ;
// 	if (current_node->tag == AST_PIPE)
// 	{
// 		printf("|\n");
// 		print_ast(current_node->data.ast_pipe.right);
// 		print_ast(current_node->data.ast_pipe.left);
// 	}
// 	if (current_node->tag == AST_EXEC)
// 	{
// 		printf("%s\n", current_node->data.ast_exec.argv[0]);
// 		return ;
// 	}
// }
void	print_env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void initialize_struct(t_shell *s, char	**envp)
{
	s->env_list = table_to_ll(envp);
	if (!s->env_list)
		terminate_shell(s);
	s->prompt = NULL;
	s->cmd_count = 0;
	s->line = NULL;
	s->old_pwd = NULL;
	s->pwd = save_cwd();
	s->old_pwd = save_cwd();
	s->head = NULL;
	s->root_node = NULL;
	s->current_node = NULL;
}


void prompt_loop(t_shell *s)
{
	//sig_setup(); //⚠️ WIP
	while (1)
	{
		//s->line = w_readline(s->prompt, s); //🚩 test
		s->line = readline(s->prompt);
		if (s->line && *s->line)
		{
			add_history(s->line);
			lexer(s);
			parser(s);
			//execution(s, &s->current_node, STDIN_FILENO, STDOUT_FILENO);
			get_fd(s->root_node);
			//simple_cmd(s); //💥 CRASH AVEC REDIR
			free_ast(&(s->root_node));
			free_list(&(s->head));
		}
		free(s->line);
	}
	free(s->sig);
}

int main(int argc, char **argv, char **envp)
{
	t_shell s;

	if (argc > 1)
	{
		printf("\nEntering Debug mode !\n\n");
		debug(argv[1]);
	}
	else
	{
		initialize_struct(&s, envp);
		create_prompt(&s);
		prompt_loop(&s);
	}
}
