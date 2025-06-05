/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/05 16:24:10 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 🚨`close` fd_out apres l'exec🚨
int	redir_out(int redir_mode, char *filename)
{
	int	fd_out;

	if (redir_mode == OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_mode == APP_OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd_out);
}

// 🚨`close` fd_in apres l'exec🚨
int	redir_in(char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	return (fd_in);
}

int	copy_args(t_list **tok, int argc, char **argv)
{
	t_list	*tmp;
	int	i;

	tmp = *tok;
	i = 0;
	while ((tmp && tmp->type != PIPE) && i < argc)
	{
		if (tmp->type == WORD && (tmp->prev == NULL
			|| tmp->prev->type == WORD || tmp->prev->type == PIPE))
		{
			argv[i] = ft_strdup(tmp->data);
			if (!argv[i])
			{
				ft_free_char_array(argv, i);
				w_free((void **)&argv);
				return (1);
			}
		}
		if (!get_next_token(&tmp))
			break;
		i++;
	}
	argv[argc] = '\0';
	return (0);
}

int	count_args(t_list **tok)
{
	t_list	*tmp;
	int		count;

	tmp = *tok;
	count = 0;
	while (tmp && tmp->type !=  PIPE)
	{
		if (tmp->type == WORD && (tmp->prev == NULL
			|| tmp->prev->type == WORD || tmp->prev->type == PIPE))
			count++;
		if (!get_next_token(&tmp))
			break;
	}
	if (count >= ARG_MAX)
	{
		errno = E2BIG;
		ft_puterror("count_args", strerror(errno));
		return (-1);
	}
	return (count);
}

// 🖨️PRINT💥DEBUGING
void	print_node(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;
	int i = 0;

	if (ast->tag == EXEC_NODE)
	{
		printf("%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		printf("%sprint_node%s| argc: %d\n", B, RST, ast->data.exec.argc);
		printf("%sprint_node%s| args:", B, RST);
		i = 0;
		while (ast->data.exec.argv[i])
		{
			printf(" [%s%s%s]", C, ast->data.exec.argv[i], RST);
			i++;
		}
		printf("\n");
		printf("%sprint_node%s| fd_in:  %d\n", B, RST, ast->data.exec.fd_in);
		printf("%sprint_node%s| fd_out: %d\n", B, RST, ast->data.exec.fd_out);
		if (ast->data.exec.heredoc == 0)
			printf("%sprint_node%s| %sNo heredoc to handle!%s\n", B, RST, R, RST);
		else if (ast->data.exec.heredoc == 1)
			printf("%sprint_node%s| %sThere's an heredoc to handle!%s\n", B, RST, G, RST);
	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.pipe.left;
		right = ast->data.pipe.right;
		printf("%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		if (left->tag == EXEC_NODE)
		{
			printf("%sprint_node%s| L. BRANCH:", B, RST);
			print_node(ast->data.pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			printf("%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);

		if (right->tag == EXEC_NODE)
		{
			printf("%sprint_node%s| R. BRANCH:", B, RST);
			print_node(ast->data.pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			printf("%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
	}
}
