/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/21 18:47:06 by emonacho         ###   ########.fr       */
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

char	**copy_heredocs(t_token *tok, int heredoc_count)
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

char	**copy_args(t_token *tok, int ac)
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

int	count_tokens(t_token **tok, int token_type)
{
	t_token	*tmp;
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
	if (count > ARG_MAX)
	{
		errno = E2BIG;
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

	fprintf(stderr, "%s====================================%s\n", G, RST);
	if (ast->tag == EXEC_NODE)
	{
		fprintf(stderr, "%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		fprintf(stderr, "%sprint_node%s| argc: %d\n", B, RST, ast->data.exec.argc);
		fprintf(stderr, "%sprint_node%s| args:", B, RST);
		i = 0;
		while (i < ast->data.exec.argc)
		{
			fprintf(stderr, " [%s%s%s]", C, ast->data.exec.argv[i], RST);
			i++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%sprint_node%s| fd_in:  %d\n", B, RST, ast->data.exec.fd_in);
		fprintf(stderr, "%sprint_node%s| fd_out: %d\n", B, RST, ast->data.exec.fd_out);
		if (ast->data.exec.heredoc_count == 0)
			fprintf(stderr, "%sprint_node%s| %sNo heredoc to handle!%s\n", B, RST, R, RST);
		else if (ast->data.exec.heredoc_count > 0)
		{
			fprintf(stderr, "%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.exec.heredoc_count)
			{
				fprintf(stderr, " [%s%s%s]", C, ast->data.exec.heredoc_list[i], RST);
				i++;
			}
			fprintf(stderr, "\n");
		}
	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.pipe.left;
		right = ast->data.pipe.right;
		fprintf(stderr, "%sprint_node%s| %sPIPE NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		if (left->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| L. BRANCH:\n", B, RST);
			print_node(ast->data.pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		fprintf(stderr, "%s------------------------------------%s\n", G, RST);
		if (right->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| R. BRANCH:\n", B, RST);
			print_node(ast->data.pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
	}
	fprintf(stderr, "%s====================================%s\n", G, RST);

}
