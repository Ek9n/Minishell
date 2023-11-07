#ifndef PARSER_H
# define PARSER_H

# define _GNU_SOURCE

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <stddef.h>
# include "../libft/libft.h"
# include "../ft_savef/ft_savef.h"
# include "minishell.h"

// typedef struct t_words
// {
// 	char	*word; //julius Lexer
// 	int		num_of_elements; //julius Lexer
// 	char	*token_after_word; //julius Lexer
//  	char 	*output; // Hannes Parser
// }	t_words;

char	*echo(char *word);
char	*getpwd(void);
int		cd(char *dir);
int		ls(char *dir);

#endif