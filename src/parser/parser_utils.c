/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:26:29 by emonacho          #+#    #+#             */
/*   Updated: 2025/07/25 13:40:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_all_heredocs(t_token *tok)
{
	int	is_a_new_pipe;
	int	heredoc_count;

	is_a_new_pipe = 1;
	heredoc_count = 0;
	while (tok)
	{
		if (tok->type == HERE_DOC && is_a_new_pipe == 1)
		{
			heredoc_count++;
			is_a_new_pipe = 0;
		}
		else if (tok->type == PIPE)
			is_a_new_pipe = 1;
		tok = tok->next;
	}
	return (heredoc_count);
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

char	**copy_eof_list(t_token *tok, int heredoc_count)
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
				ft_free_char_array(heredoc_list, heredoc_count);
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
		if (tok->type == WORD && (tok->prev == NULL
				|| tok->prev->type == WORD || tok->prev->type == PIPE))
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
	while (tmp && tmp->type != PIPE)
	{
		if (token_type == WORD && (tmp->type == WORD && (tmp->prev == NULL
					|| tmp->prev->type == WORD || tmp->prev->type == PIPE)))
			count++;
		else if (token_type == HERE_DOC && tmp->type == HERE_DOC)
			count++;
		if (!get_next_token(&tmp))
			break ;
	}
	if (count > ARG_MAX)
	{
		errno = E2BIG;
		return (-1);
	}
	return (count);
}
