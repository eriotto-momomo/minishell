/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:05 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/18 11:06:02 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

void	  lexer(t_shell *s);
int     get_token_id(char *token);
char    *get_el(char *cmd);

t_token	*create_token(char *data);
int		  add_token_back(t_token **head, char *data);
void	  add_front(t_token **head, char *data);
void	  free_token_list(t_token **head);


#endif
