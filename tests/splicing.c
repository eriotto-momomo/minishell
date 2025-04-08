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
	printf("Evaluating : %c\n", c);
	while (SEPARATORS[i])
	{
		if (c == SEPARATORS[i])
		{
			printf("%c is a sep\n", c);
			return (1);
		}
		i++;
	}
	printf("%c is not a sep\n", c);
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
	return (count);
}

char **ft_slipcing(char *cmd)
{
	int		i;
	char	**spliced;

	if (!cmd)
		return (NULL);
	i = 0;
	while (*cmd)
	{

	}
}	

t_list *ft_tokenize(char *cmd)
{
	t_list	*head;
	int		i;
	char	**spliced_cmd;

	head = NULL;
	i = 0;
	spliced_cmd = ft_slipcing(cmd);

}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("%ld\n", ft_tokencount(argv[1]));
	}
	else
		printf("No arguments\n");
}