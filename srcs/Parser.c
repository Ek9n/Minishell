#include "parser.h"

int	cmp_keyword(char *keyword, char *str)
{
	if ((ft_strcmp("echo", keyword) == 0) && (ft_strcmp("echo ", str) == 0))
		return (1);
	if ((ft_strcmp("pwd", keyword) == 0) && (ft_strcmp("pwd", str) == 0) && \
				(*(str + 3) == '\0' || *(str + 3) == ' '))// is space enough?
		return (1);
	
	return (0);
}


int	parser(t_words **INstruct, char **envp)
{
	int	i;

	i = 0;
	while (i < INstruct[0]->num_of_elements)
	{
		// if (ft_strcmp("echo ", INstruct[i].word) == 0)
		if (cmp_keyword("echo", INstruct[i]->word))
		{
			INstruct[i]->output = echo(INstruct[i]->word);
			printf("%s", INstruct[i]->output);
		}
		else if (cmp_keyword("pwd", INstruct[i]->word))
		{
			INstruct[i]->output = getpwd();
			printf("%s\n", INstruct[i]->output);
		}
		else
			//executor(INstruct[i],envp); doesnt work yet
			printf("could not find word\n");
		i++;
	}

	return (0);
}

// echo bla ls >> test.c | something

// #words:
// echo bla ls
// test.c
// something
// #tokens:
// >>
// |

// Lexer:
// >go through string and check for errors: token at the beginning more than one token next to each, 
// >go through string and check for tokens at the beginning

// while(!\0)
//  split first word (ft_strsub)
//  safe token

// char **words
// char **tokens
// or
// char ***wordsAndtokens