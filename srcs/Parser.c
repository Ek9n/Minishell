#include "parser.h"


int	cmp_keyword(char *keyword, char *str) //len integrieren mit ft_strlen
{
	int	len;

	len = ft_strlen(keyword);
	if ((ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

void	skip_prespaces(char **str)
{
	// while (**str == ' ')
		// (*str)++; // Inkrementiere den Zeiger auf die Zeichenkette, um Leerzeichen zu überspringen
	while (*(str[0]) == ' ')
		(*str)++; // Inkrementiere den Zeiger auf die Zeichenkette, um Leerzeichen zu überspringen
}

// char	*clean_spaces(char *word)
// {
// 	char	*tmp_word;

// 	tmp_word = word;
// 	printf("|%s|\n", tmp_word);
// 	skip_prespaces(&tmp_word);
// 	printf("|%s|\n", tmp_word);
// 	return (ft_strdup(tmp_word));
// }

char	*clean_spaces(char *word)
{
	char	*tmp_word;

	// tmp_word = word;
	printf("|%s|\n", word);
	skip_prespaces(&word); /// macht das sinn?... 
	word = ft_strdup(word); //FREE

	printf("|%s|\n", word);
	return (word);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	clean_word(t_words *INstruct)
{
	char	*tmp_clean;
	int		quotes; 	// 0 no, 1 single, 2 double quotes
	int		i, j;

	tmp_clean = malloc(ft_strlen(INstruct->word));
	quotes = 0;
	i = 0;
	j = 0;
	i += skip_spaces(&INstruct->word[i]);
	while (INstruct->word[i] != '\0')
	{
		if (INstruct->word[i] == ' ' && quotes == 0)
		{
			i += skip_spaces(&INstruct->word[i]);
			i--;
		}
		if (INstruct->word[i] == '\'' && quotes == 0)
			quotes = 1;
		else if (INstruct->word[i] == '\'' && quotes == 1)
			quotes = 0;
		if (INstruct->word[i] == '\"' && quotes == 0)
			quotes = 2;
		else if (INstruct->word[i] == '\"' && quotes == 2)
			quotes = 0;

		if (INstruct->word[i] == '$' && quotes != 1)
		{
			tmp_clean[j] = '@';
			j++;
		}
		else if (!((INstruct->word[i] == '\'' && quotes != 2) || 
				(INstruct->word[i] == '\"' && quotes != 1)))
		{
			tmp_clean[j] = INstruct->word[i];
			j++;
		}

		i++;
	}
	while (tmp_clean[--j] == ' ');
	tmp_clean[j + 1] = '\0';
	INstruct->word_clean = ft_strdup(tmp_clean);
	free(tmp_clean);
}

void	clean_words(t_words **INstruct)
{
	int	i;

	i = 0;
	while (i < INstruct[0]->num_of_elements)
	{
		clean_word(INstruct[i]);
		i++;
	}
}

int	parser(t_words **INstruct)
{
	int	i;

	// char tmpword[] = "  echo   bla bla\"bla\" kann  ";
	// INstruct[0]->word = tmpword; // temporary, cuz the lexer do some mistakes while errorchecking
	clean_words(INstruct);

// export env 
	char *user = getenv("A");

	if (user != NULL) {
		printf("Der Benutzername ist: %s\n", user);
	} else {
		printf("Die Umgebungsvariable USER existiert nicht.\n");
	}


	i = 0;
		// printf("elements:%d\n",INstruct[0]->num_of_elements);
		printf("FWord:|%s|\n",INstruct[0]->word);
		printf("FWord:|%s|\n",INstruct[0]->word_clean);
	while (i < INstruct[0]->num_of_elements)
	{
		// printf("word=%s\n", INstruct[i]->word);
		// if (ft_strcmp("echo ", INstruct[i].word) == 0)
		if (cmp_keyword("echo", INstruct[i]->word_clean))
		{
			// echo(INstruct[i]->word);
			INstruct[i]->output = echo(INstruct[i]->word_clean);
			printf("%s", INstruct[i]->output);
		}
		else if (cmp_keyword("pwd", INstruct[i]->word_clean))
		{
			INstruct[i]->output = getpwd();
			printf("%s\n", INstruct[i]->output);
		}
		else if (cmp_keyword("cd", INstruct[i]->word_clean))
		{
			cd(INstruct[i]->word_clean);
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
		else if (cmp_keyword("ls", INstruct[i]->word_clean))
		{
			ls(INstruct[i]->word_clean);
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