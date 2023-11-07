/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/07 16:21:09 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <stdbool.h>

# include "parser.h"
# include "executor.h" // is it good with headders? may we put all here in minishell.h and every file links to minishell.h
# include "enviroment.h"

// typedef struct t_words
// {
// 	char	*word; //julius Lexer
// 	char	*word_clean; //Hannes Parser
// 	int		num_of_elements; //julius Lexer
// 	int		quotes_case;
// 	char	*token_after_word; //julius Lexer
//  	char 	*output; // Hannes Parser
// }	t_words;

typedef struct t_words
{
	char	*word; //julius Lexer
	char	*word_clean; //Hannes Parser
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	char 	**enviroment;
	int		redirection;
}		t_words;

// LEXER
enum	errors {
	ALLOCERR,
	SYNERR,		
};
void	puterr(int err);
// 
int		parser(t_words **INstruct);

int		ft_strcmp(const char *s1, const char *s2);


#endif