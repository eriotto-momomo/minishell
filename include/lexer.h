/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:26:05 by emonacho          #+#    #+#             */
/*   Updated: 2025/06/20 09:35:57 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

int		lexer(t_shell *s);
int		get_token_id(char *token);
char	*get_el(char *cmd);

t_token	*create_token(char *data);
int		add_token_back(t_token **head, char *data);
void	add_front(t_token **head, char *data);
void	free_token_list(t_token **head);


#endif
