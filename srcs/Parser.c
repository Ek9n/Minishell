#include "parser.h"

// int	cmp_keyword(char *keyword, char *str)
// {
// 	if ((ft_strcmp("echo", keyword) == 0) && (ft_strcmp("echo", str) == 0) && \
// 			(*(str + 4) == '\0' || *(str + 4) == ' '))
// 	// if ((ft_strcmp("echo", keyword) == 0) && (ft_strcmp("echo ", str) == 0))
// 		return (1);
// 	if ((ft_strcmp("pwd", keyword) == 0) && (ft_strcmp("pwd", str) == 0) && \
// 			(*(str + 3) == '\0' || *(str + 3) == ' '))// is space enough?
// 		return (1);
// 	if ((ft_strcmp("cd", keyword) == 0) && (ft_strcmp("cd", str) == 0) && \
// 			(*(str + 2) == '\0' || *(str + 2) == ' '))// is space enough?
// 		return (1);
// 	if ((ft_strcmp("ls", keyword) == 0) && (ft_strcmp("ls", str) == 0) && \
// 			(*(str + 2) == '\0' || *(str + 2) == ' '))
// 		return (1);
// 	return (0);
// }


int	cmp_keyword(char *keyword, char *str, int len)
{
	if ((ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

int	parser(t_words **INstruct)
{
	int	i;

	i = 0;
	while (i < INstruct[0]->num_of_elements)
	{
		printf("word=%s\n", INstruct[i]->word);
		// if (ft_strcmp("echo ", INstruct[i].word) == 0)
		if (cmp_keyword("echo", INstruct[i]->word, 4))
		{
			// echo(INstruct[i]->word);
			INstruct[i]->output = echo(INstruct[i]->word);
			printf("%s", INstruct[i]->output);
		}
		else if (cmp_keyword("pwd", INstruct[i]->word, 3))
		{
			INstruct[i]->output = getpwd();
			printf("%s\n", INstruct[i]->output);
		}
		else if (cmp_keyword("cd", INstruct[i]->word, 2))
		{
			cd(INstruct[i]->word);
			// if (chdir(" ") != 0)
			// 	printf("shit happens1!\n");
			// if (chdir("") != 0)
			// 	printf("shit happens2!\n");
			// if (chdir("..") != 0)
			// 	printf("shit happens3!\n");
			// if (chdir(" ..") != 0)
			// 	printf("shit happens4!\n");
			// if (chdir(".. ") != 0)
			// 	printf("shit happens5!\n");

			// INstruct[i]->output = cd(char *dir);
			// printf("%s\n", INstruct[i]->output);
		}
		else if (cmp_keyword("ls", INstruct[i]->word, 2))
		{
			ls(INstruct[i]->word);
		}
		else
			printf("(parser) could not find word\n");
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