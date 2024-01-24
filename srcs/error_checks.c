#include "minishell.h"

int	valid_input(char *str)
{
	if(quote_error(str))
		return (0);
	return (1);
}

int	quote_error(char *str)
{
	int	i;
	int	quote; // 1 for ', 2 for "

	quote = 0;
	i = -1;
	while(str[++i])
	{
		if ((quote == 1 && str[i] == '\'') || (quote == 2 && str[i] == '\"'))
			quote = 0;
		else if (quote != 2 && str[i] == '\'')
			quote = 1;
		else if (quote != 1 && str[i] == '\"')
			quote = 2;
		// printf("(quote_error_checker) %d\n", i);
		// printf("(quote_error_checker) quote:%d\n", quote);
	}
	if (quote != 0)
	{
		printf("(quote_error) problem in inputstr!\n");
		return (1);
	}
	return (0);
}
