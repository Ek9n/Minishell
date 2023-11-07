#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef	struct t_redirections
{
	char *str1;
	char *str2;
	int fd_in;
	int fd_out;
} 	t_redirections;


int		ft_strcmp(const char *s1, const char *s2);
char	*echo(char *word);
char	*getpwd(void);
int		cd(char *dir);

#endif