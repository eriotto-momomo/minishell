# include "../include/minishell.h"

int	is_space(char c)
{
	if (c == 32 || c >= 9 && c <= 13)
		return (1);
	return(0);
}

int	is_sep(char c)
{
	int i;
	
	i = 0;
	while (SEPARATORS[i])
	{
		if (c == SEPARATORS[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_tokencount(char *cmd)
{
	size_t	count;
	int		i;
	int		in_token;

	i = 0;
	count = 0;
	in_token = 0;
	while (cmd[i])
	{
		if (is_sep(cmd[i]) || is_space(cmd[i]))
		{
			if (is_sep(cmd[i]))
				count++;
			in_token = 0;
		}
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		i++;
	}
	printf("%ld token(s) found !\n", count);
	return (count);
}


// static char *push_sep(char *cmd)
// {
// 	char *new
// }
// Duplique la string passe en parametre jusqu'au prochain SEPARATORS, bouge la pointeur a cette position
static char	*push_word(char **cmd)
{
	char	*new_str;
	int		i;

	i = 0;
	while (!(is_sep((*cmd)[i]) || is_space((*cmd)[i])))
		i++;
	new_str = malloc((sizeof(char) * i) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (**cmd && !(is_sep(**cmd) || is_space(**cmd)))
	{
		new_str[i++] = **cmd;
		(*cmd)++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char **cmd_splicing(char *cmd)
{
	char	**spliced;
	int		i;

	if (!cmd)
		return (NULL);
	spliced = malloc((ft_tokencount(cmd) * sizeof(char *)) + 1);
	if (!spliced)
		return (NULL);
	while (*cmd)
	{
		if (is_sep(*cmd))
		{
			spliced[i] = malloc(sizeof(char) * 2);
			spliced[i][0] = *cmd;
			spliced[i][1] = '\0';
			i++;
			cmd++;
		}
		else
			spliced[i++] = push_word(&cmd);
		while (is_space(*cmd))
			cmd++;
	}
	spliced[i] = NULL;
	return(spliced);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		char **spliced;
		spliced = cmd_splicing(argv[1]);
		for (size_t i = 0; spliced[i]; i++)
			printf("%s\n", spliced[i]);
		
	}
}

// t_list *ft_tokenize(char *cmd)
// {
// 	t_list	*head;
// 	int		i;
// 	char	**spliced_cmd;

// 	head = NULL;
// 	i = 0;
// 	spliced_cmd = ft_slipcing(cmd);

// }