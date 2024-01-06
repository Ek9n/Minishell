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
		if(words[i]->redirection->whole_command != NULL)
			 while (words[i]->redirection->whole_command[b])
			{
				printf("whole_command_redirection: %s\n",words[i]->redirection->split_command[b]);
				b++;
			}
		printf("fd_in: %d\n",words[i]->redirection->fd_in);
		printf("fd_out: %d\n",words[i]->redirection->fd_out);
		printf("quotes_case: %d\n",words[i]->quotes_case);
		printf("\n");
		printf("\n");
		i++;
	}
}
char *ft_join(char **arr)
{
    int i = 0;
    int total_length = 0;
    size_t current_length = 0;

    while (arr[i] != NULL)
    {
        total_length += ft_strlen(arr[i]);
        i++;
    }

    char *str = (char *)malloc((total_length + i + 1) * sizeof(char));
    if (!str)
        return NULL;

    str[0] = '\0';
    i = 0;
    while (arr[i] != NULL)
    {
        current_length += ft_strlcat(str, arr[i], total_length + i + 1);
        if (arr[i + 1] && arr[i + 1][0] != '\0')
            current_length += ft_strlcat(str, " ", total_length + i + 1);
        i++;
    }

    return str;
}
void free_and_close_data(t_data *data)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (data->INstruct[i] != NULL)
	{
		free(data->INstruct[i]->word);
		free(data->INstruct[i]->word_clean);
		free(data->INstruct[i]->token_after_word);
		free(data->INstruct[i]->output);
		if(data->INstruct[i]->redirection->whole_command != NULL)
		{
			while (data->INstruct[i]->redirection->whole_command[b])
			{
				free(data->INstruct[i]->redirection->split_command[b]);
				b++;
			}
		free(data->INstruct[i]->redirection->whole_command);
		free(data->INstruct[i]->redirection->split_command);
		close(data->INstruct[i]->redirection->fd_in);
		close(data->INstruct[i]->redirection->fd_out);
		}
		free(data->INstruct[i]->redirection);
		free(data->INstruct[i]);
		i++;
	}
	ft_putnbr_fd(g_exit_status, 1);
	if (g_exit_status == 69)
	{
		close(data->original_fd_in);
		close(data->original_fd_out);
		free(data->INstruct);
		b = 0;
		while(data->envp[b])
		{
			free(data -> envp[b]);
			b++;
		}
		free(data->envp);
		free(data);
		g_exit_status = 0;
		exit(EXIT_SUCCESS);
	}
		if (g_exit_status >= 129)
			exit(EXIT_FAILURE);
}