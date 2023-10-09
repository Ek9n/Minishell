/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/10/08 11:27:03 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct t_words
{
	char	*word; //julius Lexer
	int		num_of_elements; //julius Lexer
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
}		t_words;
# define _GNU_SOURCE

# include <signal.h>
 #include <stdio.h>
 #include <readline/readline.h>
 #include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include "./libft/libft.h"

#endif