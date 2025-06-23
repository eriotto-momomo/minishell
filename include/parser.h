/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emonacho <emonacho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:50:04 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/23 10:44:01 by emonacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		add_command(t_ast **node, t_token **tok);
int		add_redir(t_ast **node, t_token **tok);
t_ast	*add_exec_node(t_token **tok);
t_ast	*add_pipe_node(t_ast *left, t_ast *right);
t_ast	*new_ast_node(t_ast node);
int		parser(t_shell *s);
t_ast	*build_ast(t_token **tok);
t_ast	*parse_pipe(t_token **tok);
t_ast	*parse_line(t_token **tok);
t_ast	*parse_exec(t_token **tok);
void	get_next_pipe(t_token **tok);
int		get_next_token(t_token **tok);
char	**copy_args(t_token *tok, int ac);
char	**copy_heredocs(t_token *tok, int heredoc_count);
int		redir_out(int redir_mode, char *filename, int current_redir);
int		redir_in(char *filename, int current_redir);
t_ast	*new_ast_node(t_ast node);
int		count_tokens(t_token **tok, int token_type);
int		syntax_analysis(t_shell *s, t_token *tok);

#endif
