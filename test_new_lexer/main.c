# include "../includes/minishell.h"

int 	get_num_of_pipes(char * str)
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
void 	replace_spaces_and_pipes_in_quotes(char *input)
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
int		redir_case(char *c)
{
	if ((*c == '<' && *(c + 1) == '<') || (*c == '>' && *(c + 1) == '>'))
		return (2);
	else if (*c == '<' || *c == '>')
		return (1);
	return (0);
}
void	detect_quote(char *dirty_word, bool *quotes, int *last_quote)
{
	if (*quotes == false && (dirty_word[0] == '\'' || dirty_word[0] == '\"'))
	{
		*quotes = true;
		if (dirty_word[0] == '\'')
			*last_quote = 1;
		else if (dirty_word[0] == '\"')
			*last_quote = 2;

	}
	else if (*quotes == true && *last_quote == 1 && dirty_word[0] == '\'')
	{
		*quotes = false;
		*last_quote = 0;
	}
	else if (*quotes == true && *last_quote == 2 && dirty_word[0] == '\"')
	{
		*quotes = false;
		*last_quote = 0;
	}
}
void	redirection_space_extender3(char **dirty_word)
{
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
	while (dirty_word[0][i])
	{
		detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		if (!quotes && redir_case(&dirty_word[0][i]) == 1)
		{
			tmp_word2[j++] =  ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] =  ' ';
			detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		}
		else if (!quotes && redir_case(&dirty_word[0][i]) == 2)
		{
			tmp_word2[j++] =  ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] =  ' ';
			detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		}
		tmp_word2[j] = dirty_word[0][i];
		j++;
		i++;
	}
	tmp_word2[j] = '\0';
	free(dirty_word[0]);
	dirty_word[0] = ft_strdup(tmp_word2);
	free(tmp_word2);
}
int		skip_spaces(char *str)
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
	int		i;
	int		j;

	tmp_clean = malloc(ft_strlen(*command));
	i = 0;
	j = 0;
	i += skip_spaces(*command);
	while (command[0][i] != '\0')
	{
		if (command[0][i] == ' ')
		{
			i += skip_spaces(&command[0][i]);
			tmp_clean[j++] = ' ';
		}
		else
			tmp_clean[j++] = command[0][i++];
	}
	while (tmp_clean[--j] == ' ');
	tmp_clean[j + 1] = '\0';
	free(*command);
	*command = ft_strdup(tmp_clean);
	free(tmp_clean);
}
void 	putback_spaces_and_pipes_in_quotes(char *input)
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
		if (input[i] == '@' && (quotes == 1 || quotes == 2))
			input[i] = ' ';
		if (input[i] == '$' && (quotes == 1 || quotes == 2))
			input[i] = '|';
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_words	**nodes;
	char 	**buffer;
	int		i;
	int		a;

	while (true)
	{
		i = 0;
		a = 0;
		input = readline("Minishell>>: ");
		replace_spaces_and_pipes_in_quotes(input);
		redirection_space_extender3(&input);
		nodes = ft_calloc(get_num_of_pipes(input) + 2, sizeof(t_words *));
		buffer = ft_split(input, '|');
		while (buffer[i] != NULL)
		{
			nodes[a] = ft_calloc(1, sizeof(t_words)); // protect
			nodes[a]->command = buffer[i];
			
			clean_spaces_in_command(&nodes[a]->command);

			a++;
			i++;
		}
		// #bring back the spaces //for now testing.. first split and redirections..
		a = 0;
		while (nodes[a] && nodes[a]->command)
		{
			putback_spaces_and_pipes_in_quotes(nodes[a]->command);
			printf("%s\n",nodes[a]->command);
			a++;
		}
		a = 0;
		// fflush(0);		
	}
}