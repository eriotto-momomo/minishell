/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:40 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/09 00:03:57 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* simple_token_interpreter(STI):
*	- Lis le premier `token` trouvé
*	- Si il correspond à une fonction existante dans l'environnement `minishell`
*		->	Check si le `token` est suivi d'une option
*		--> Appel la fonction avec/sans options, et avec le/les arguments
*
*	Par exemple si on fait `echo -n HELLO` dans `minishell`:
*	1. STI va lire `line_read` (dans prompt_loop)
*	2. Il détecte `echo` puis si:
*	0️⃣✅ FONCTION RECONNUE 1️⃣ Check les options
*	0️⃣❌ FONCTION INCONNUE 1️⃣ "minishell-1.0$ Error: [FUNCTION_NAME] unknown."
*	2️⃣✅ OPTION(S) RECONNUE(S) 3️⃣ Appel la fonction avec le/les arguments
*	2️⃣❌ OPTION(S) INCONNUE(S) 3️⃣ "minishell-1.0$ Error: [FUNCTION_NAME]'s [OPTION_NAME] unknown." /
*	"minishell-1.0$ Error: [FUNCTION_NAME] takes only [N] arguments."
*	4️⃣✅ ARGUMENT(S) VALIDE(S) 🟢 La fonction fonctionne! "HELLO"🐬
*	4️⃣❌  ARGUMENT(S) INVALIDE(S) 🔴 La fonction retourne un message d'erreur "Ouch!"💥
*/

/*
* FONCTIONNE DE MANIÈRE TRÈS SOMMAIRE, À AMÉLIORER POUR FONCTIONNER PARFAITEMENT
* AVEC LE SPLICING ET L'AST
* ⚠️ WIP ⚠️
* - Trouver un moyen d'identifier les fonctions reconnues ainsi que leurs options facilement
* - check_if_handled | ft_strnstr ne fonctionne pas pour cet usage, faire un `filter`
*/

//void	check_if_handled(t_shell *s, char *function, char *option)
void	check_if_handled(t_shell *s, char *function)
{
	if (!ft_strnstr(s->builtins->func_list, function,
			ft_strlen(s->builtins->func_list)))
	{
		ft_puterror("check_if_handled", "Function unknown.");
		return ;
	}
	else
		printf(G"function: `%s` is handled!\n"RST, function);
}

char	*get_token(char *line_read, size_t *i)
{
	size_t	token_start;
	size_t	j;
	char	*token;

	while(ft_isspace(line_read[*i]))
		(*i)++;
	/*if (!ft_isalpha(line_read[*i]) && line_read[*i] != '-') //(!ft_isallowed_cmd_chars(line_read[i])
		return (NULL);*/
	token_start = *i;
	while(ft_isalpha(line_read[*i]) || line_read[*i] == '-')
		(*i)++;
	token = malloc(sizeof(char) * (*i - token_start) + 1);
	if (token == NULL)
		return (NULL);
	j = 0;
	while (token_start < *i)
		token[j++] = line_read[token_start++];
	token[j] = '\0';
	return (token);
}

// Fais uniquement pour tester `echo -n`
int	simple_token_interpreter(t_shell *s, char *line_read)
{
	size_t	i;
	char	*function;
	char	*option;
	i = 0;

	if (line_read == NULL)
		return (0);
	function = get_token(line_read, &i);
	if (function == NULL)
		return (0);
	option = get_token(line_read, &i);
	if (option == NULL)
	{
		free(function);
		return (0);
	}
	printf("function: %s\noption: %s\n", function, option);
	//check_if_handled(s, function, option);
	check_if_handled(s, function);
	free(function);
	free(option);
	return (1);
}