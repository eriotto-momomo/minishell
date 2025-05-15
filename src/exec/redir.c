/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:06:41 by emonacho          #+#    #+#             */
/*   Updated: 2025/05/15 16:50:53 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//⚠️ infinite loop de redirs?


int	redirect(int mode, int fd)
{
	int	error;

	error = 0;
	if (mode == OUT_REDIR)
		error = dup2(fd, STDOUT_FILENO);
	else if (mode == IN_REDIR)
		error = dup2(fd, STDIN_FILENO);
	else if (mode == HERE_DOC)
		printf("%sHEREDOC NOT HANDLED!%s\n", R, RST);
	if (error < 0)
	{
		ft_puterror("redirect", strerror(errno));
		return (-1);
	}
	return (1);
}

int	dup_shell(int mode)
{
	int	fd;

	fd = -1;
	if (mode == OUT_REDIR)
		fd = dup(STDOUT_FILENO);
	else if (mode == IN_REDIR)
		fd = dup(STDIN_FILENO);
	else if (mode == HERE_DOC)
		printf("%sHEREDOC NOT HANDLED!%s\n", R, RST);
	if (fd < 0)
	{
		ft_puterror("dup_shell", strerror(errno));
		return (-1);
	}
	return (fd);
}

// '>'	fd = 1, O_CREAT | O_WRONLY |  O_TRUNC	-> mode = 1 (redir output)(creating / overwriting)
// '>>'	fd = 1, O_CREAT | O_WRONLY | O_APPEND	-> mode = 2 (redir output)(appending)
// '<'	fd = 0, O_RDONLY						-> mode = 3 (redir input)(reading)
// '<<'	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
int	w_open_redir(char *file_path, int mode)
{
	int	fd;

	fd = -1;
	if (mode == OUT_REDIR)
		fd = open(file_path, O_CREAT | O_WRONLY |  O_TRUNC, 0644);
	else if (mode == APP_OUT_REDIR)
		fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (mode == IN_REDIR)
		fd = open(file_path, O_RDONLY);
	else if (mode == HERE_DOC)
		printf("%sHEREDOC NOT HANDLED!%s\n", R, RST);
	if (fd < 0)
	{
		errno = ENOENT;
		ft_puterror("w_open_redir", strerror(errno));
		return (-1);
	}
	return (fd);
}

//	Write [ast_redir.left] output to [ast_redir.filename]
//	Voir HEREDOC syntax
// ...
int	heredoc(t_ast *node)
{
	printf("Redirect INPUT in %sHEREDOC%s mode\n", Y, RST);
	(void)node;
	printf("%sHEREDOC NOT HANDLED!%s\n", R, RST);

	return (1);
}

//	Append [ast_redir.left] output to [ast_redir.filename]
//	1. If filename exists -> append content
//	2. If not -> create and write
int	append_cmd_output(t_ast *node)
{
	printf("Redirect OUTPUT in %sAPPEND%s mode\n", Y, RST);
	int	redir_out;
	//int	std_out;

	redir_out = open(node->data.ast_redir.filename, O_CREAT | O_WRONLY | O_APPEND);
	//std_out = open(STDOUT_FILENO, O_RDONLY);
	//if (redir_out < 0 || std_out < 0)
	if (redir_out < 0)
	{
		errno = ENOENT;
		return (ft_puterror("append_cmd_output", strerror(errno)));
	}
	//if (dup2(std_out, redir_out) < 0)
	if (dup2(1, redir_out) < 0)
	{
		close(redir_out);
		//close(std_out);
		return (ft_puterror("trunc_cmd_output", strerror(errno)));
	}
	//close(std_out);
	return (1);
}



//	Write [ast_redir.left] output to [ast_redir.filename]
//	1. If filename exists -> overwrite content
//	2. If not -> create and write
int	trunc_cmd_output(t_ast *node)
{
	printf("Redirect OUTPUT in %sCREATE/TRUNCATE%s mode\n", Y, RST);
	int	redir_out;
	int	shell_save;

	redir_out = w_open_redir(node->data.ast_redir.filename, OUT_REDIR);
	if (redir_out < 0)
		return (0);
	shell_save = dup_shell(OUT_REDIR);
	if (shell_save < 0)
		return (close(redir_out));
	if (redirect(OUT_REDIR, redir_out) < 0)
	{
		close(shell_save);
		close(redir_out);
		return (0);
	}
	close(redir_out);


	// EXECUTER LA COMMANDE
	write(1, "trunc_cmd_output | 🔥🔥🔥🔥🔥🔥🔥TEST🔥🔥🔥🔥🔥🔥🔥\n", 50);
	printf("trunc_cmd_output | 🔥🔥🔥🔥🔥🔥🔥TEST🔥🔥🔥🔥🔥🔥🔥\n");


	if (redirect(OUT_REDIR, shell_save) < 0)
	{
		close(shell_save);
		return (0);
	}
	close(shell_save);
	return (1);
}

// `cat` works with redirected file input, `echo` doesn't!
int	redirect_cmd_input(t_ast *node)
{
	printf("Redirect INPUT in %sREAD%s mode\n", Y, RST);
	int	redir_in;
	//int	std_in;

	redir_in = open(node->data.ast_redir.filename, O_RDONLY);
	//std_in = open(STDIN_FILENO, O_RDONLY);
	if (redir_in < 0)
	{
		errno = ENOENT;
		return (ft_puterror("redirect_cmd_input", strerror(errno)));
	}




	return (1);
}

// '>'	fd = 1, O_CREAT | O_WRONLY |  O_TRUNC	-> mode = 1 (redir output)(creating / overwriting)
// '>>'	fd = 1, O_CREAT | O_WRONLY | O_APPEND	-> mode = 2 (redir output)(appending)
// '<'	fd = 0, O_RDONLY						-> mode = 3 (redir input)(reading)
// '<<'	fd = 0, O_RDONLY | ... ?				-> mode = 4 (redir input)(here doc)
int		test_redir(t_ast *node)
{
	//int	restore;

	if (node->tag == AST_REDIR)
		printf("test_redir | %sAST_REDIR found!%s ", G, RST);
	else {
		printf("test_redir | %sNo AST_REDIR found!%s\n", R, RST);
		return (0); }
	if (node->data.ast_redir.mode == 1 || node->data.ast_redir.mode == 2)
	{
		//restore = dup(STDOUT_FILENO);
		if (node->data.ast_redir.mode == 1)
			trunc_cmd_output(node);
		else if (node->data.ast_redir.mode == 2)
			append_cmd_output(node);
		//dup2(restore, STDIN_FILENO);
		//printf("test_redir | %sRESTORE STDOUT%s\n", Y, RST);
	}
	else
	{
		//restore = dup(STDIN_FILENO);
		if (node->data.ast_redir.mode == 3)
			redirect_cmd_input(node);
		else if (node->data.ast_redir.mode == 4)
			heredoc(node);
		//dup2(restore, STDIN_FILENO);
		//printf("test_redir | %sRESTORE STDIN%s\n", Y, RST);
	}
	//close(restore);
	return (1);
}
