#include "minishell.h"

int	cmp_keyword(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword);
	if ((ft_strcmp(keyword, str) == 0) && \
			(*(str + len) == '\0' || *(str + len) == ' '))
		return (1);
	return (0);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
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

void	redirection_space_extender(char **dirty_word)
{
	char	*q_start;
	char	*q_end;
	char	**extd_words;
	char	*tmp_word;
	char	*extd_word;
	bool	quotes;
	int		i;

	extd_words = ft_split(*dirty_word, '<');
	quotes = false;
	i = 0;
	while (extd_words[i])
	{
		if (i != 0 && extd_words[i][0] != ' ')
		{
			tmp_word = ft_strjoin(" ", extd_words[i]);
			free(extd_words[i]);
			extd_words[i] = tmp_word;
			// free(tmp_word);
		}
		if (extd_words[i + 1] != NULL && extd_words[i][ft_strlen(extd_words[i]) - 1] != ' ')
		{
			tmp_word = ft_strjoin(extd_words[i], " <");
			free(extd_words[i]);
			extd_words[i] = tmp_word;
		}
		else if (extd_words[i + 1] != NULL)
		{
			tmp_word = ft_strjoin(extd_words[i], "<");
			free(extd_words[i]);
			extd_words[i] = tmp_word;		
		}
		i++;
	}
	extd_word = comb_extd_word(extd_words);
	i = 0;
	while (extd_words[i])
		free(extd_words[i++]);
	free(extd_words);
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

void	clean_word2(t_words *INstruct)
{
	char	*tmp_clean;
	int		quotes; 	// 0 no, 1 single, 2 double quotes
	int		i, j;
	tmp_clean = malloc(ft_strlen(INstruct->word));
	// redirection_space_extender2(&INstruct->word);
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

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	free_piperino(char **cmd1, char *path1)
{
	int	i;

	i = 0;
	while(cmd1[i] != NULL)
		free(cmd1[i++]);
	free(cmd1);
	free(path1);
}

static void	free_piperino2(t_words *INstruct, char **cmd1, char *path1) //Instruct hinzufuegen und auf NULL prüfen
{
	int	i;

	i = 0;
	if (INstruct != NULL)
	{
		while(cmd1[i] != NULL)
			free(cmd1[i++]);
		if (cmd1 != NULL)
			free(cmd1);
		if (path1 != NULL)
			free(path1);
	}
}

void	printpipe(int read_fd)
{
	char	buffer[999];
	read(read_fd, buffer, 10);
	printf("%s\n", buffer);
}

int	cnt_pipes(t_words **INstruct)
{
	int	 i;

	i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && \
			INstruct[i]->token_after_word[0] == '|')
		i++;
	return (i);
}

static int	is_pipe(t_words **INstruct, int i)
{
	if (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && \
			INstruct[i]->token_after_word[0] == '|')
		return (1);
	return (0);
}

static int	is_redirection(t_words **INstruct, int i)
{
	if (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && \
			(INstruct[i]->token_after_word[0] == '>' || \
			INstruct[i]->token_after_word[0] == '<'))
		return (1);
	return (0);
}

int	single_command(t_data *data,int i)
{
	// printf("in single_command:%s\n", data->INstruct[i]->word_clean);
	if (cmp_keyword("echo", data->INstruct[i]->word_clean))
	{
		data->INstruct[i]->output = echo(data->INstruct[i]->word_clean);
		printf("%s", data->INstruct[i]->output);
	}
	else if (cmp_keyword("pwd",data->INstruct[i]->word_clean))
	{
		data->INstruct[i]->output = getpwd();
		printf("%s\n", data->INstruct[i]->output);
	}
	else if (cmp_keyword("cd", data->INstruct[i]->word_clean))
		cd(data->INstruct[i]->word_clean, &data->envp);
	else if (cmp_keyword("export", data->INstruct[i]->word_clean))
	{
		unset(data->INstruct[i]->word_clean, &data->envp);
		export(data->INstruct[i]->word_clean, &data->envp);
	}
	else if (cmp_keyword("unset", data->INstruct[i]->word_clean))
		unset(data->INstruct[i]->word_clean, &data->envp);
	else if (cmp_keyword("env", data->INstruct[i]->word_clean))
		printenv(data->envp);
	else if (cmp_keyword("exit", data->INstruct[i]->word_clean))
		free_and_close_data(data, 0);
	else
		exec_cmd(data->INstruct[i]->word_clean, data);
	return (0);
}

int	piperino8(t_words **INstruct,t_data *data)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
	int		i;
	int		j;

	// printf("FD IS>%d\n\n", INstruct[0]->redirection->fd_in);
    i = 0;
    j = 0;
    pipe_fd = malloc(200 * sizeof(int *));
    while (is_pipe(INstruct, j))
    {
        pipe_fd[j] = malloc(2 * sizeof(int));
        if (pipe(pipe_fd[j]) == -1)
            error_exit("(piperino6) Pipe creation failed\n");
        j++;
    }
    while (INstruct[i] != NULL)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if ( INstruct[i]->redirection->whole_command != NULL)
			{
				get_fds(data, i);
				data->INstruct[i]->word_clean = ft_join(data->INstruct[i]->redirection->split_command);
				dup2(INstruct[i]->redirection->fd_in, STDIN_FILENO); //may we have to undo the redirection later.. idk yet
				close(INstruct[i]->redirection->fd_in);
			}
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            if (is_pipe(INstruct, i))
            {
				if (INstruct[i]->redirection->whole_command != NULL)
					dup2(INstruct[i]->redirection->fd_out, STDOUT_FILENO);
				else	
			    	dup2(pipe_fd[i][1], STDOUT_FILENO);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
			j = i;
			while (is_pipe(INstruct, j))
			{
                close(pipe_fd[j][0]);
                close(pipe_fd[j][1]);	
				j++;		
			}
            cmd1 = ft_split(INstruct[i]->word_clean, ' ');
        	path1 = ft_strjoin("/bin/", cmd1[0]);
			execve(path1, cmd1, NULL);
            perror("(piperino6) Exec1 failed");
        }
        else
        {
            if (i != 0)
            {
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
        }
		//free_piperino2(INstruct[i], cmd1, path1);
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (is_pipe(INstruct, j))
        {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
        }
    }
    for (int j = 0; j < i; j++)
    {
        waitpid(pids[j], NULL, 0);
    }
    return (i);
}
void print_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	printf("whole_command:%s\n", redirection->whole_command);
	printf("fd_in:%d\n", redirection->fd_in);
	printf("fd_out:%d\n", redirection->fd_out);
	while (redirection->split_command[i] != NULL)
	{
		printf("split_command[%d]:%s\n", i, redirection->split_command[i]);
		i++;
	}
	printf("\n");
	printf("====================================");
	printf("\n");

}

int	ft_heredoc(char * delimiter)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	line = ft_calloc(1, sizeof(char));
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break;	//add variable expansion
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (fd);
}
void get_fds(t_data *data,int index)
{
	int	i;
	int here;

	here = 0;
	i = 0;
	if (data->INstruct[index]->redirection->whole_command != NULL)
	{
		while (data->INstruct[index]->redirection->split_command[i])
		{	
			if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 4)
				{
					i = ft_heredoc(data->INstruct[index]->redirection->split_command[i + 1]);
					break;
				}
				else
					i++;
		}
	i = 0;
	while (data->INstruct[index]->redirection->split_command[i])
	{
		if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 3) // >
		{
			data->INstruct[index]->redirection->fd_out = open(data->INstruct[index]->redirection->split_command[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (data->INstruct[index]->redirection->fd_out == -1)
			{
				dup2(data->original_fd_in, 0);
				dup2(data->original_fd_out, 1);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed", 1);
			}	
			data->INstruct[index]->redirection->split_command[i][0] = '\0';
			data->INstruct[index]->redirection->split_command[i + 1][0] = '\0';
			data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command);
			dup2(data->INstruct[index]->redirection->fd_out, STDOUT_FILENO);	
			//close(data->INstruct[index]->redirection->fd_out);
		}
		if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 5) // >>
		{
			data->INstruct[index]->redirection->fd_out = open(data->INstruct[index]->redirection->split_command[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);				//protect open
			if (data->INstruct[index]->redirection->fd_out == -1)
			{
				dup2(data->original_fd_in, 0);
				dup2(data->original_fd_out, 1);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed", 1);
			}	
			data->INstruct[index]->redirection->split_command[i][0] = '\0';
			data->INstruct[index]->redirection->split_command[i + 1][0] = '\0';
			data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command);
			dup2(data->INstruct[index]->redirection->fd_out, STDOUT_FILENO);
		}
		if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 2) // <
		{
			data->INstruct[index]->redirection->fd_in = open(data->INstruct[index]->redirection->split_command[i + 1], O_RDONLY);
			if (data->INstruct[index]->redirection->fd_in == -1)
			{
				dup2(data->original_fd_in, 0);
				dup2(data->original_fd_out, 1);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("open failed, file doesnt exist probably", 1);
			}
			data->INstruct[index]->redirection->split_command[i][0] = '\0';
			data->INstruct[index]->redirection->split_command[i + 1][0] = '\0';
			data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command);
			dup2(data->INstruct[index]->redirection->fd_in, STDIN_FILENO);
		}
		if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 4) // <<
		{ 
			data->INstruct[index]->redirection->fd_in = open(".heredoc", O_RDONLY);
			if (data->INstruct[index]->redirection->fd_in == -1)
			{
				dup2(data->original_fd_in, 0);
				dup2(data->original_fd_out, 1);
				close(data->original_fd_in);
				close(data->original_fd_out);
				ft_putstr_fd("Heredoc failed to create a temp file.", 1);
			}
			data->INstruct[index]->redirection->split_command[i][0] = '\0';
			data->INstruct[index]->redirection->split_command[i + 1][0] = '\0';
			data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command);
			dup2(data->INstruct[index]->redirection->fd_in, STDIN_FILENO);
		}
		i++;
	}
		data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command); //free
	}
}

int Executor(t_data *data)
{
	int	i;
	int redir;

	redir = 0;
	i = 0;
	while (i < data->INstruct[0]->num_of_elements)
	{
		if (is_pipe(data->INstruct, i))
		{
			clean_words(data->INstruct);
			piperino8(data->INstruct + i,data);
			break;
		}
		else
		{
			// printf("2-singlecommand: %s//\n", data->INstruct[i]->word);
			if (data->INstruct[i]->redirection->whole_command != NULL)
				get_fds(data, i);
			clean_words(data->INstruct);
			single_command(data, i);
		}
		i++;
	}
	return (i);
}
