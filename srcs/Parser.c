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
/*
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

void	redirection_space_extende
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
*//*
int	redir_case(char *c)
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
*//*
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

*/
void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
// static int	is_pipe(t_words **INstruct, int i)
// {
// 	if (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && \
// 			INstruct[i]->token_after_word[0] == '|')
// 		return (1);
// 	return (0);
// }
int	single_command(t_data *data,int i)
{
	// printf("in single_command:%s\n", data->INstruct[i]->word_clean);
	if (cmp_keyword("echo", data->nodes[i]->split_command[0]))
	{
		data->nodes[i]->output = echo(data->nodes[i]->command);
		printf("%s", data->nodes[i]->output);
	}
	else if (cmp_keyword("pwd",data->nodes[i]->split_command[0]))
	{
		data->nodes[i]->output = getpwd();
		printf("%s\n", data->nodes[i]->output);
	}
	else if (cmp_keyword("cd", data->nodes[i]->split_command[0]))
		cd(data->nodes[i]->split_command[1], &data->envp);
	else if (cmp_keyword("export", data->nodes[i]->split_command[0]))
	{
		unset(data->nodes[i]->command, &data->envp);
		export(data->nodes[i]->command, &data->envp);
	}
	else if (cmp_keyword("unset", data->nodes[i]->split_command[0]))
		unset(data->nodes[i]->split_command[1], &data->envp);
	else if (cmp_keyword("env", data->nodes[i]->split_command[0]))
		printenv(data->envp);
	else if (cmp_keyword("exit", data->nodes[i]->split_command[0]))
		//free_and_close_data(data, 0);
		exit(0);
	else
		exec_cmd(data->nodes[i]->split_command, data);
	return (0);
}
// /*
int	piperino8(t_words **nodes,t_data *data)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
	int		i;
	int		j;
	int		pipes_cnt;

	// printf("FD IS>%d\n\n", INstruct[0]->redirection->fd_in);
    pipes_cnt = 0;
    pipe_fd = malloc(data->numb_of_pipes * sizeof(int *)); //make sure to cnt pipes here before
    while (pipes_cnt < data->numb_of_pipes)
    {
        pipe_fd[pipes_cnt] = malloc(2 * sizeof(int));
        if (pipe(pipe_fd[pipes_cnt]) == -1)
            error_exit("(piperino6) Pipe creation failed\n");
        pipes_cnt++;
    }
            printf("PIPES:%d, orignum:%d:\n", pipes_cnt, data->numb_of_pipes);

    i = 0;
    // while (pipes_cnt >= 0)
    while (nodes[i] != NULL)
    {
            printf("PEP2-NodesAddr:%p\n", nodes[i]);

        pids[i] = fork();
        if (pids[i] == 0)
        {
            // if (nodes[i]->command != NULL)
            // if (nodes[i]->fd_in != data->original_fd_in)
			// {
			// 	get_fds(data, i);
			// 	nodes[i]->command = ft_join(nodes[i]->split_command); //free? .. do we need it like that?...
			// 	// nodes[i]->command = ft_join(nodes[i]->split_command); //free? .. do we need it like that?...
            // 	printf("PEP22:%s:\n", nodes[i]->command);
				
			// 	dup2(nodes[i]->fd_in, STDIN_FILENO); //may we have to undo the redirection later.. idk yet
			// 	close(nodes[i]->fd_in);
			// }
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            	printf("PEP3:\n");

		        // if (nodes[i]->fd_out != data->original_fd_out)
				// 	dup2(nodes[i]->fd_out, STDOUT_FILENO);
				// else	
			    	dup2(pipe_fd[i][1], STDOUT_FILENO);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            // }
			j = i;
			// while (is_pipe(nodes, j))
			while (j <= pipes_cnt)
			{
            	printf("PEP4:\n");

                close(pipe_fd[j][0]);
                close(pipe_fd[j][1]);	
				j++;		
			}
            // cmd1 = ft_split(nodes[i]->command, ' ');
            cmd1 = nodes[i]->split_command;
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
		pipes_cnt--;
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (j < pipes_cnt)
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
// */
int Executor(t_data *data)
{
	int	i;
	int redir;

	redir = 0;
	i = 0;
	while(data->nodes[i])
	{
		if (data->numb_of_pipes > 0)
		{
			piperino8(data->nodes, data);
			// piperino8(data->command + i,data);
			break ;
		}
		else
			single_command(data, i);
		i++;
	}
	return (i);
}
