# include "../includes/minishell.h"

int get_num_of_pipes(char * str)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (str[a])
	{
		if (str[a] == '|')
			i++;
		a++;
	}	
	return(i);
}
void replace_spaces_in_quotes(char *input)
{
	int		quotes; 	// 0 no, 1 single, 2 double quotes
	int		i, j;
	quotes = 0;
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && quotes == 0)
			quotes = 1;
		else if (input[i] == '\'' && quotes == 1)
			quotes = 0;
		if (input[i] == '\"' && quotes == 0)
			quotes = 2;
		else if (input[i] == '\"' && quotes == 2)
			quotes = 0;
		if (input[i] == ' ' && (quotes == 1 || quotes == 2))
			input[i] = '@';
		if (input[i] == '|' && (quotes == 1 || quotes == 2))
			input[i] = '$';
		i++;
	}
}

char	*comb_extd_word(char **extd_words)
{
	char	*tmp_word;
	char	*comb_word;
	int	i;

	tmp_word = NULL;
	comb_word = NULL;
	i = 0;
	while (extd_words[i])
	{
		// if (comb_word == NULL)
		if (i == 0)
		{
			comb_word = ft_strdup("");
		}

		tmp_word = ft_strjoin(comb_word, extd_words[i]);
		free(comb_word);
		comb_word = tmp_word;
		// free(tmp_word)??? -> than we could implement strdup

		i++;
	}
	return (comb_word);
}

int	redir_case(char *c)
{
	if ((*c == '<' && *(c + 1) == '<') || (*c == '>' && *(c + 1) == '>'))
		return (2);
	else if (*c == '<' || *c == '>')
		return (1);
	return (0);
}
void	redirection_space_extender2(char **dirty_word)
{
	// printf("DIRTY1|%s|\n", *dirty_word);

	int		i;
	int		j;
	char	*tmp_word2;
	bool	quotes;
	int		last_quote;

	tmp_word2 = malloc(ft_strlen(*dirty_word) * 2);
	quotes = false;
	last_quote = 0; // 1 = single, 2 = double quotes
	i = 0;
	j = 0;
	// printf("START\n");
	while (dirty_word[0][i])
	{
		// printf("%c", dirty_word[0][i]);
		if (quotes == false && (dirty_word[0][i] == '\'' || dirty_word[0][i] == '\"'))
		{
			quotes = true;
			if (dirty_word[0][i] == '\'')
				last_quote = 1;
			else if (dirty_word[0][i] == '\"')
				last_quote = 2;

		}
		else if (quotes == true && last_quote == 1 && dirty_word[0][i] == '\'')
		{
			quotes = false;
			last_quote = 0;
		}
		else if (quotes == true && last_quote == 2 && dirty_word[0][i] == '\"')
		{
			quotes = false;
			last_quote = 0;
		}



		if (!quotes && redir_case(&dirty_word[0][i]) == 1)
		{
			tmp_word2[j++] =  ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] =  ' ';
		}
		else if (!quotes && redir_case(&dirty_word[0][i]) == 2)
		{
			tmp_word2[j++] =  ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] =  ' ';
		}
		tmp_word2[j] = dirty_word[0][i];

		j++;
		i++;
	}
	tmp_word2[j] = '\0';
	// printf("DIRTY2|%s|\n", tmp_word2);
	// printf("\nEND\n");
	free(dirty_word[0]);
	dirty_word[0] = ft_strdup(tmp_word2);
	free(tmp_word2);


}
int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	clean_spaces_in_command(char **command)
{
	char	*tmp_clean;
	int		quotes; 	// 0 no, 1 single, 2 double quotes
	int		i, j;
	tmp_clean = malloc(ft_strlen(*command));
	quotes = 0;
	i = 0;
	j = 0;
	i += skip_spaces(*command);
	while (*command[i] != '\0')
	{
		if (*command[i] == ' ' && quotes == 0)
		{
			i += skip_spaces(*command);
			i--;
		}
		if (*command[i] == '\'' && quotes == 0)
			quotes = 1;
		else if (*command[i] == '\'' && quotes == 1)
			quotes = 0;
		if (*command[i] == '\"' && quotes == 0)
			quotes = 2;
		else if (*command[i] == '\"' && quotes == 2)
			quotes = 0;
		else if (!((*command[i] == '\'' && quotes != 2) || 
				(*command[i] == '\"' && quotes != 1)))
		{
			tmp_clean[j] = *command[i];
			j++;
		}

		i++;
	}
	while (tmp_clean[--j] == ' ');
	tmp_clean[j + 1] = '\0';

	free(*command);
	*command = ft_strdup(tmp_clean);
	free(tmp_clean);
}
int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_words 			**nodes;
	char 				**buffer;
	int					i;
	int					a;
	i = 0;
	a = 0;

	while (true)
	{
		
		input = readline("Minishell>>: ");
		replace_spaces_in_quotes(input);
		nodes = ft_calloc(get_num_of_pipes(input) + 2, sizeof(t_words *));
		buffer = ft_split(input, '|');
		while (buffer[i] != NULL)
			{
				nodes[a] = ft_calloc(1, sizeof(t_words )); // protect
				nodes[a]->command = buffer[i];
				redirection_space_extender2(&nodes[a]->command);
				//clean_spaces_in_command(&nodes[a]->command);
			while(nodes[a]->command)
			{
				printf("%s\n",nodes[a]->command);
				a++;
			}
			}
			fflush(0);		
	}
}