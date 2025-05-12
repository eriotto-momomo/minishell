/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/12 11:33:22 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//⚠️ infinite loop de redirs?

//	Write [ast_redir.left] output to [ast_redir.filename]
//	Voir HEREDOC syntax
// ...
int	heredoc(t_shell *s, char *output_path)
{
	printf("Redirect INPUT in %sHEREDOC%s mode\n", Y, RST);
	(void)s;
	(void)output_path;

	return (1);
}

//	Append [ast_redir.left] output to [ast_redir.filename]
//	1. If filename exists -> append content
//	2. If not -> create and write
int	append_cmd_output(t_shell *s, char *output_path)
{
	printf("Redirect OUTPUT in %sAPPEND%s mode\n", Y, RST);
	(void)s;
	(void)output_path;

	return (1);
}

//	Write [ast_redir.left] output to [ast_redir.filename]
//	1. If filename exists -> overwrite content
//	2. If not -> create and write
int	trunc_cmd_output(t_shell *s, char *output_path)
{
	printf("Redirect OUTPUT in %sCREATE/TRUNCATE%s mode\n", Y, RST);
	(void)s;
	(void)output_path;

	return (1);
}

// `cat` works with redirected file input, `echo` doesn't!
int	redirect_cmd_input(t_shell *s, char *input_path)
{
	printf("Redirect INPUT in %sREAD%s mode\n", Y, RST);
	(void)s;
	(void)input_path;
	int	input;

	input = open(input_path, O_RDONLY);
	if (input < 0)
	{
		errno = ENOENT;
		return (ft_puterror("redirect_cmd_input", strerror(errno)));
	}




	return (1);
}

// '<'	fd = 0, O_RDONLY						-> mode = 1 (redir input)(reading)
// '>'	fd = 1, O_WRONLY | O_CREATE | O_TRUNC	-> mode = 2 (redir output)(creating / overwriting)
// '>>'	fd = 1, O_WRONLY | O_CREATE				-> mode = 3 (redir output)(appending)
// '<<'	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
void	test_redir(t_shell *s)
{
	if (s->root_node->tag == AST_REDIR)
	{
		printf("test_redir | %sAST_REDIR found!%s ", G, RST);
		if (s->root_node->data.ast_redir.mode == 1)
			redirect_cmd_input(s, NULL);
		else if (s->root_node->data.ast_redir.mode == 2)
			trunc_cmd_output(s, NULL);
		else if (s->root_node->data.ast_redir.mode == 3)
			append_cmd_output(s, NULL);
		else if (s->root_node->data.ast_redir.mode == 4)
			heredoc(s, NULL);
	}
	else
		printf("test_redir | %sNo AST_REDIR found!%s\n", R, RST);
}
