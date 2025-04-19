/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:11 by emonacho          #+#    #+#             */
/*   Updated: 2025/04/19 19:12:41 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_ast	*block_cmd(t_ast *ast, ??? );
// t_ast	*pipe_cmd(t_ast *ast, ??? );
// t_ast	*line_cmd(t_ast *ast, ??? );
// t_ast	*redir_cmd(t_ast *ast, char *file_name, int oflag, int fd);
// t_ast	*exec_cmd(t_ast *ast, ??? );

/* `t_ast	*redir_cmd(t_ast *ast, char *file_name, int oflag, int fd);`
* t_ast *ast: pointeur sur le `sub-tree`
* char *file_name: pointeur sur le nom du fichier dans lequel rediriger
* int oflag: mode de lecture (`O_RDONLY | O_WRONLY | O_CREATE | O_TRUNC`)
* int fd: 0 si < | <<, 1 si > | >> */
/*
t_ast	*redir_cmd(t_ast *ast, char *file_name, int oflag, int fd)
{
	...
}
*/