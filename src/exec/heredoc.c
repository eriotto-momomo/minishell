/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:25:02 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/30 09:21:09 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	put_in_heredoc(char *line, int fd)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	if (!new_line)
		return (1);
	ft_putstr_fd(new_line, fd);
	free(new_line);
	return (0);
}

// 🚧 DELIMITER -> doit etre une 'str', si celle-ci commence et fini par des quotes, l'expansion de variable est desactivee. 🚧
// 🚧 DELIMITER -> si il est appele entre quotes, son appel final n'a pas besoin de l'etre. 🚧
int	is_delimiter(char *line, char *delimiter)	// 🚨 A TESTER!
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (delimiter[j] && (delimiter[j] == '\'' || delimiter[j] == '\"'))
		j++;
	if (line[i] == delimiter[j])
	{
		while (line[i] && delimiter[j]
			&& (line[i] == delimiter[j]))
		{
			i++;
			j++;
		}
		if (line[i] == '\0' && (delimiter[j] == '\0'
			|| delimiter[j] == '\''|| delimiter[j] == '\"'))
			return (1);
	}
	return (0);
}

int	handle_heredoc(t_shell *s, t_ast *current_node)
{
	char	*ptr;

	ptr = current_node->data.ast_redir.filename;
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	// 🚨 ON ARRIVE ICI AVEC LE DERNIER HEREDOC DETECTE 🚨
	// Si: `cat << 1 << 2 << 3 << 4` ---> `s->fd` est égal au fd de 4
	// Les `EOF` se ferment de gache a droite donc:
	// ⚪ 1. Récupérer la liste des délimiteurs précédents
	// ----> Fonction qui recupere tous les `filename`
	// ⚪ 2. Si l'EOF est appelé dans le bon ordre et que le prochain EOF n'est pas le dernier
	// le contenu de `heredoc_tmp` est overwrite jusqu'au prochain EOF.
	// ----> Fonction qui consomme les EOF
	// ⚪ 3. Si l'EOF appelé correspond au dernier de la liste on `break` et on envoie ce fd.
	// ----> On free la liste de delimiteurs
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, current_node->data.ast_redir.filename))
			break ;
		if ((ptr[0] != '\'' && ptr[ft_strlen(ptr)] != '\'')		// 🚨 A TESTER!
			&& (ptr[0] != '\"' && ptr[ft_strlen(ptr)] != '\"'))	// 🚨 A TESTER!
			expand(s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	if (close(s->fd) < 0)
		return (-1);
	printf("handle_heredoc| %shandle_redir SUCCEED!%s\n", G, RST);
	return (0);
}

// BACKUP💾
/*int	handle_heredoc(t_shell *s)
{
	char	*ptr;

	ptr = s->root_node->data.ast_redir.filename;
	s->fd = open(s->heredoc_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (s->fd < 0)
		return (-1);
	reset_prompt(s, HEREDOC_PROMPT);
	while (1)
	{
		s->line = readline("> ");
		if (!s->line)
			break;
		if (is_delimiter(s->line, s->root_node->data.ast_redir.filename))
			break ;
		if ((ptr[0] != '\'' && ptr[ft_strlen(ptr)] != '\'')		// 🚨 A TESTER!
			&& (ptr[0] != '\"' && ptr[ft_strlen(ptr)] != '\"'))	// 🚨 A TESTER!
			expand(s->env_list, &(s->line));
		if (put_in_heredoc(s->line, s->fd) != 0)
			return (-1);
		w_free((void **)&s->line);
	}
	w_free((void **)&s->line);
	if (close(s->fd) < 0)
		return (-1);
	return (0);
}*/
