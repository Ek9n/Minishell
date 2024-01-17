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
void 	print_nodes(t_words **nodes)
{
	int i;
	int a;
	i = 0;
	a = 0;
	while (nodes[i])
	{
		printf("command at pos %i: %s\n", i,nodes[i]->command);
		while (nodes[i]->split_command[a])
		{
			printf("split_command at node %i, pos %i: %s\n", i,a,nodes[i]->split_command[a]);
			a++;
		}
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
}/*
void free_and_close_data(t_data *data,int status)
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
	if (status != 2)
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
		if (status == 1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}

}*/