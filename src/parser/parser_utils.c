/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/13 15:28:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_out(int redir_mode, char *filename, int current_redir)
{
	int	fd_out;

	if (current_redir > 2)
	{
		//printf("redir_out| %sclosing current_redir: %d%s\n", P, current_redir, RST);	// 🖨️PRINT💥DEBUGING
		if (close(current_redir) < 0)
			return (-1);
	}
	if (redir_mode == OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_mode == APP_OUT_REDIR)
		fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	//printf("redir_out| %sfilename: %s | fd_out: %d%s\n", P, filename, fd_out, RST);		// 🖨️PRINT💥DEBUGING
	return (fd_out);
}

int	redir_in(char *filename, int current_redir)
{
	int	fd_in;

	if (current_redir > 2)
	{
		//printf("redir_in | %sclosing current_redir: %d%s\n", P, current_redir, RST);	// 🖨️PRINT💥DEBUGING
		if (close(current_redir) < 0)
			return (-1);
	}
	fd_in = open(filename, O_RDONLY);
	//printf("redir_in | %sfilename: %s | fd_in:  %d%s\n", P, filename, fd_in, RST);		// 🖨️PRINT💥DEBUGING
	return (fd_in);
}

t_ast	*new_ast_node(t_ast node)
{
	t_ast	*ptr;

	ptr = malloc(sizeof(t_ast));
	if (!ptr)
		return (NULL);
	*ptr = node;
	return (ptr);
}

char	**copy_heredocs(t_list *tok, int heredoc_count)
{
	char	**heredoc_list;
	int		i;

	heredoc_list = malloc(sizeof(char **) * heredoc_count);
	if (!heredoc_list)
		return (NULL);
	i = 0;
	while (tok && i < heredoc_count)
	{
		if (tok->type == HERE_DOC)
		{
			heredoc_list[i] = ft_strdup(tok->next->data);
			if (!heredoc_list[i])
			{
				ft_free_char_array(heredoc_list, i);
				return (NULL);
			}
			i++;
		}
		tok = tok->next;
	}
	return (heredoc_list);
}

char	**copy_args(t_list *tok, int ac)
{
	char	**av;
	int		i;

	av = malloc(sizeof(char **) * (ac + 1));
	if (!av)
		return (NULL);
	i = 0;
	while (tok && i < ac)
	{
		if (tok->type == WORD)
		{
			av[i] = ft_strdup(tok->data);
			if (!av[i])
			{
				ft_free_char_array(av, i);
				return (NULL);
			}
			i++;
		}
		tok = tok->next;
	}
	av[i] = NULL;
	return (av);
}



int	copy_tokens(t_list **tok, int token_type, int size, char **array)
{
	t_list	*tmp;
	int	i;

	tmp = *tok;
	i = 0;
	while (tmp && tmp->type != PIPE && i < size)
	{
		if ((tmp->type == WORD || tmp->type == HERE_DOC) && (tmp->prev == NULL
			|| tmp->prev->type == WORD || tmp->prev->type == PIPE))
		{
			if (tmp->type == WORD && token_type == WORD)
			{
				array[i] = ft_strdup(tmp->data);
				i++;
			}
			else if (tmp->type == HERE_DOC && token_type == HERE_DOC)
			{
				array[i] = ft_strdup(tmp->next->data);
				i++;
			}

			if (!array[i])
			{
				ft_free_char_array(array, i);
				return (1);
			}
		}
		if (!get_next_token(&tmp))
			break;
	}
	return (0);
}

int	count_tokens(t_list **tok, int token_type)
{
	t_list	*tmp;
	int		count;

	tmp = *tok;
	count = 0;
	while (tmp && tmp->type !=  PIPE)
	{
		if (token_type == WORD && (tmp->type == WORD && (tmp->prev == NULL
			|| tmp->prev->type == WORD || tmp->prev->type == PIPE)))
			count++;
		else if (token_type == HERE_DOC && tmp->type == HERE_DOC)
			count++;
		if (!get_next_token(&tmp))
			break;
	}
	if (count >= ARG_MAX)
	{
		errno = E2BIG;
		ft_puterror("count_tokens", strerror(errno));
		return (-1);
	}
	return (count);
}

// 🖨️PRINT💥DEBUGING
void print_struct(t_shell *s)
{
	printf("%sprint_struct%s | s->ret_value %s%d%s\n", G, RST, C, s->ret_value, RST);
	printf("%sprint_struct%s | s->heredoc_count %s%d%s\n", G, RST, C, s->heredoc_count, RST);
	printf("%sprint_struct%s | s->fd %s%d%s\n", G, RST, C, s->fd, RST);
	printf("%sprint_struct%s | s->final_output_fd %s%d%s\n", G, RST, C, s->final_output_fd, RST);
	printf("%sprint_struct%s | s->stdin_save %s%d%s\n", G, RST, C, s->stdin_save, RST);
	printf("%sprint_struct%s | s->stdout_save %s%d%s\n", G, RST, C, s->stdout_save, RST);
	printf("%sprint_struct%s | s->node_initialized %s%d%s\n", G, RST, C, s->node_initialized, RST);
	printf("%sprint_struct%s | s->pipefd[0] %s%d%s\n", G, RST, C, s->pipefd[0], RST);
	printf("%sprint_struct%s | s->pipefd[1] %s%d%s\n", G, RST, C, s->pipefd[1], RST);
	if (s->prompt)
		printf("%sprint_struct%s | s->prompt [%s%s%s]\n", G, RST, C, s->prompt, RST);
	if (s->line)
		printf("%sprint_struct%s | s->line [%s%s%s]\n", G, RST, C,  s->line,RST);
	if (s->heredoc_tmp)
		printf("%sprint_struct%s | s->heredoc_tmp [%s%s%s]\n", G, RST, C, s->heredoc_tmp, RST);
	if (s->heredoc_list)
		for (size_t i = 0; s->heredoc_list[i]; i++)
			printf("%sprint_struct%s | s->heredoc_list[%ld][%s%s%s]\n", G, RST, i, C, s->heredoc_tmp, RST);
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
		while (i < ast->data.exec.argc)
		{
			printf(" [%s%s%s]", C, ast->data.exec.argv[i], RST);
			i++;
		}
		printf("\n");
		printf("%sprint_node%s| fd_in:  %d\n", B, RST, ast->data.exec.fd_in);
		printf("%sprint_node%s| fd_out: %d\n", B, RST, ast->data.exec.fd_out);
		if (ast->data.exec.heredoc_count == 0)
			printf("%sprint_node%s| %sNo heredoc to handle!%s\n", B, RST, R, RST);
		else if (ast->data.exec.heredoc_count > 0)
		{
			printf("%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.exec.heredoc_count)
			{
				printf(" [%s%s%s]", C, ast->data.exec.heredoc_list[i], RST);
				i++;
			}
			printf("\n");
		}
	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.pipe.left;
		right = ast->data.pipe.right;
		printf("%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		if (left->tag == EXEC_NODE)
		{
			printf("%sprint_node%s| L. BRANCH:\n", B, RST);
			print_node(ast->data.pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			printf("%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		printf("%s------------------------------------%s\n", G, RST);
		if (right->tag == EXEC_NODE)
		{
			printf("%sprint_node%s| R. BRANCH:\n", B, RST);
			print_node(ast->data.pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			printf("%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
	}
}
