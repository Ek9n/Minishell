/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:07:11 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/05 15:28:58 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define _GNU_SOURCE

# include "minishell.h"


int		is_in_quotes(char * line);
int check_token_syntax(char *str);
char	*trimstr(char *str,int i);
char *tokenizer(char **line);

#endif