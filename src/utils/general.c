/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:34:21 by timmi             #+#    #+#             */
/*   Updated: 2025/07/05 15:55:05 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_node(t_ast *ast) // 🖨️PRINT💥DEBUGING
{
	t_ast	*left;
	t_ast	*right;
	int i = 0;

	if (ast->tag == EXEC_NODE)
	{
		fprintf(stderr, "%s====================================%s\n", G, RST);
		fprintf(stderr, "%sprint_node%s| %sEXEC NODE%s\n", B, RST, G, RST);
		fprintf(stderr, "%s....................................%s\n", G, RST);
		fprintf(stderr, "%sprint_node%s| argc: %d\n", B, RST, ast->data.s_exec.ac);
		fprintf(stderr, "%sprint_node%s| args:", B, RST);
		i = 0;
		while (i < ast->data.s_exec.ac)
		{
			fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.av[i], RST);
			i++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%sprint_node%s| fd_in:  %s%d%s\n", B, RST, C, ast->data.s_exec.fd_in, RST);
		fprintf(stderr, "%sprint_node%s| fd_out: %s%d%s\n", B, RST, C, ast->data.s_exec.fd_out, RST);
		fprintf(stderr, "%sprint_node%s| inredir_priority: %d\n", B, RST, ast->data.s_exec.inredir_priority);
		if (ast->data.s_exec.path_tmp_file != NULL)
			fprintf(stderr, "%sprint_node%s| path_tmp_file:  %s%s%s\n", B, RST, C, ast->data.s_exec.path_tmp_file, RST);
		if (ast->data.s_exec.eof_count == 0)
			fprintf(stderr, "%sprint_node%s| No heredoc to handle\n", B, RST);
		else if (ast->data.s_exec.eof_count > 0)
		{
			fprintf(stderr, "%sprint_node%s| heredoc:", B, RST);
			i = 0;
			while (i < ast->data.s_exec.eof_count)
			{
				fprintf(stderr, " [%s%s%s]", C, ast->data.s_exec.eof_list[i], RST);
				i++;
			}
			fprintf(stderr, "\n");
		}
		fprintf(stderr, "%s====================================%s\n", G, RST);

	}
	else if (ast->tag == PIPE_NODE)
	{
		left = ast->data.s_pipe.left;
		right = ast->data.s_pipe.right;
		fprintf(stderr, "%s====================================%s\n", P, RST);
		fprintf(stderr, "%sprint_node%s| %sPIPE NODE%s\n", B, RST, P, RST);
		fprintf(stderr, "%s....................................%s\n", P, RST);
		if (left->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| L. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.left);
		}
		else if (left->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| L. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		fprintf(stderr, "%s------------------------------------%s\n", P, RST);
		if (right->tag == EXEC_NODE)
		{
			fprintf(stderr, "%sprint_node%s| R. BRANCH:\n", B, RST);
			print_node(ast->data.s_pipe.right);
		}
		else if (right->tag == PIPE_NODE)
			fprintf(stderr, "%sprint_node%s| R. BRANCH: [%spipe%s]\n", B, RST, P, RST);
		fprintf(stderr, "%s====================================%s\n", P, RST);
	}
} // 🖨️PRINT💥DEBUGING  // 🖨️PRINT💥DEBUGING  // 🖨️PRINT💥DEBUGING // 🖨️PRINT💥DEBUGING

int	is_open(int fd)
{
	struct stat buf;

	if (fstat(fd, &buf) == 0)
		return 1;
	else
		return 0;
}

void	v_switch(char **s, char *new_s)
{
	w_free((void **)s);
	*s = new_s;
}

size_t	count_var(t_env *head)
{
	size_t	count;

	count = 0;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

char	**ltotable(t_env *head)
{
	int		i;
	char	**env_table;
	char	*tmp;
	size_t	len;

	i = 0;
	len = count_var(head);
	env_table = malloc(sizeof(char *) * (len + 1));
	if (!env_table)
		return (NULL);
	while (head)
	{
		tmp = ft_str3join(head->name, "=", head->value);
		if (!tmp)
		{
			ft_free_char_array(env_table, len);
			return (NULL);
		}
		env_table[i++] = tmp;
		head = head->next;
	}
	env_table[i] = NULL;
	return (env_table);
}

int	perfect_match(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if ((ft_strlen(s1) == ft_strlen(s2))
		&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}
