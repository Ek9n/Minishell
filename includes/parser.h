#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"


int		ft_strcmp(const char *s1, const char *s2);
char	*echo(char *word);
char	*getpwd(void);
int		cd(char *dir);

#endif