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