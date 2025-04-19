/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:04 by timmi             #+#    #+#             */
/*   Updated: 2025/04/18 17:48:53 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_sep(char c)
{
	int	i;

	i = 0;
	while (SEPARATORS[i])
	{
		if (c == SEPARATORS[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_quote(char *cmd, int i)
{
	char	quote;
	char	*str;
	size_t	len;

	quote = cmd[i];
	len = 1;
	while (cmd[i + len] && cmd[i + len] != quote)
		len++;
	len++;
	str = malloc((sizeof(char) * len + 1));
	if (!str)
		return (NULL);
	len = 0;
	str[len++] = cmd[i++];
	while (cmd[i] && cmd[i] != quote)
		str[len++] = cmd[i++];
	str[len++] = cmd[i];
	str[len] = '\0';
	return (str);
}

char	*get_sep(char *cmd, int i)
{
	char	*sep;

	if ((cmd[i] == '<' && cmd[i + 1] == '<')
		|| (cmd[i] == '>' && cmd[i + 1] == '>'))
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (NULL);
		sep[0] = cmd[i];
		sep[1] = cmd[i];
		sep[3] = '\0';
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (NULL);
		sep[0] = cmd[i];
		sep[1] = '\0';
	}
	return (sep);
}

char	*get_word(char *cmd, int i)
{
	size_t	len;
	char	*word;

	len = 0;
	while (cmd[i + len] && !(is_sep(cmd[i + len]) || ft_isspace(cmd[i + len])))
		len++;
	word = malloc((sizeof(char) * len) + 1);
	if (!word)
		return (NULL);
	len = 0;
	while (cmd[i] && !(is_sep(cmd[i]) || ft_isspace(cmd[i])))
		word[len++] = cmd[i++];
	word[len] = '\0';
	return (word);
}

int	debug(char *path)
{
	t_list	*head;
	int 	fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("=================================");
		printf("\nCmd to tokenize : %s %s %s\n", C, line, RST);
		head = tokenize(line);
		print_list(head);
	}
	return (0);
}

void	print_list(t_list *head)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		printf("Node n. %d\n", i++);
		printf("Data :%s %s %s\n",G, temp->data, RST);
		printf("Type : %s %d %s\n", G, temp->type, RST);
		printf("=======================================\n");
		temp = temp->next;
	}
}