#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;
	
	n = ft_strlen(s1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
void free_dirty_words(t_words **words) 
{
	int i;

	i = 0;
    while (words[i])
	{
		words[i]-> word_clean = ft_strdup(words[i]->word);
        free((words[i])->word);
        (*words)->word = NULL;
        words++;
    }
}
void 	print_words(t_words **words)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (words[i] != NULL)
	{
		printf("word: %s\n",words[i]->word_clean);
		printf("token: %s\n",words[i]->token_after_word);
		printf("num_of_elements: %d\n",words[i]->num_of_elements);
		if(words[i]->redirection->whole_command)
			 printf("redir: yes\n");
		else
			printf("redir: no\n");
		printf("fd_in: %d\n",words[i]->redirection->fd_in);
		printf("fd_out: %d\n",words[i]->redirection->fd_out);
		printf("quotes_case: %d\n",words[i]->quotes_case);
		printf("\n");
		printf("\n");
		i++;
	}
}
