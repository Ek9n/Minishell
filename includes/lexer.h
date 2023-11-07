/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:07:11 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/07 23:26:58 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define _GNU_SOURCE

# include "minishell.h"
# include "enviroment.h"

int		is_in_quotes(char * line);
int		check_token_syntax(char *str);
char	*trimstr(char *str,int i);
char	*tokenizer(char **line);
t_words	**init_word_stack(char *line, t_words **words, char **envp);

#endif