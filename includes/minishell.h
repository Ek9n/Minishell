/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:38:26 by jfoltan           #+#    #+#             */
/*   Updated: 2023/11/05 15:39:23 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "lexer.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../ft_savef/ft_savef.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include "parser.h"
# include "executor.h"

typedef struct t_words
{
	char	*word; //julius Lexer
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	char 	**enviroment;
}		t_words;

// LEXER
enum	errors {
	ALLOCERR,
	SYNERR,		
};
void	puterr(int err);
// 
int		parser(t_words **INstruct);
char	**arrdup(char **enviroment);
t_words	**init_word_stack(char *line,t_words **words,char **envp);

#endif