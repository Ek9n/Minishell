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

void	skip_prespaces(char **str)
{
	while (*(str[0]) == ' ')
		(*str)++; 
}

char	*clean_spaces(char *word)
{
	char	*tmp_word;

	skip_prespaces(&word); /// macht das sinn?... 
	word = ft_strdup(word); //FREE // WTF
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
		executor(data->INstruct[i]->word_clean, data);
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
            if (i == 0  && INstruct[0]->redirection->whole_command != NULL)
			{
				get_fds(data, i);
				data->INstruct[i]->word_clean = ft_join(data->INstruct[i]->redirection->split_command);
				dup2(INstruct[0]->redirection->fd_in, STDIN_FILENO); //may we have to undo the redirection later.. idk yet
				close(INstruct[0]->redirection->fd_in);
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
	while (ft_strcmp(line, delimiter) != 0)
	{
		line = readline(">");
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);		
}
void get_fds(t_data *data,int index)
{
	int	i;

	i = 0;
	if (data->INstruct[index]->redirection->whole_command != NULL)
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
			//close(data->INstruct[index]->redirection->fd_in);
		}
		/*if (check_token_syntax(data->INstruct[index]->redirection->split_command[i]) == 4) // <<
		{ 
			data->INstruct[index]->redirection->fd_in = ft_heredoc(data->INstruct[index]->redirection->split_command[i + 1]);
		}*/
		i++;
	}
		data->INstruct[index]->word_clean = ft_join(data->INstruct[index]->redirection->split_command); //free
}
int Executor2(t_data *data)
{
	int	i;
	int redir;

	redir = 0;
	i = 0;
	while (find_char_from_index(data->INstruct[i]->word_clean,'$',0) != -1)
			data->INstruct[i]->word_clean = expand_env(data->INstruct[i]->word_clean, data->envp); //still have to handle quotes
	while (i < data->INstruct[0]->num_of_elements)
	{
		//if (data->INstruct[i]->redirection->whole_command != NULL)
		//{
			//get_fds(data, i);
			//redir = 1;
		//}
		if (is_pipe(data->INstruct, i))
		{
			piperino8(data->INstruct + i,data);
			break;
		}
		else
		{
			if (data->INstruct[i]->redirection->whole_command != NULL)
				get_fds(data, i);
			single_command(data, i);
		}
		//dup2(data->original_fd_in, 0);
		//dup2(data->original_fd_out, 1);
		i++;
	}
	return (i);
	/* cat < file2 > test | wc writes to test, and not to stdout. 
		because piperino makes i+= idk what/when etc, it makes closing fds and stuff hard.
		freeing and execve failure too, im unsure whether its correct. 
	 */
}
/*
int	piperino8(t_words **INstruct, int i)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
	int		j;

    j = i;
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
printf("wordinpep[%i]:%s\n", i, INstruct[i]->word_clean);
printf("wordinpep[%i]:%s\n", i + 1, INstruct[i + 1]->word_clean);

        cmd1 = ft_split(INstruct[i]->word_clean, ' ');
        path1 = ft_strjoin("/bin/", cmd1[0]);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            if (is_pipe(INstruct, i))
            {
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
        free_piperino2(INstruct[i], cmd1, path1);
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
*/
/*
executor 
commands pipes redirections.

*/
/*
int Executor(t_words **words)


		if simple command: (NO PIPE)
			1. check for redirections
				in case command has a < or << token, we have to go from right, until only tokens > or >> are left
				afterwards we have to check if the command is a keyword
				ONLY ONE COMMAND WITH ONE INPUT CAN BE LEFT BEFORE WE GET TO 2.
			2. check if command is a keyword witch cat.
			3.execve
		if pipe:
			get the output of the first command
				1. check for redirections
					in case command has a < or << token, we have to go from right, until only tokens > or >> are left
					afterwards we have to check if the command is a keyword
					ONLY ONE COMMAND WITH ONE INPUT CAN BE LEFT BEFORE WE GET TO 2.
			2. check if command is a keyword
				if it was redirected, putstr_fd with cat
				if not dup2
			3.
			
			while (words[i])
			{
				if simple 
				{
					if check redirection
						do redirection(it should rewrite contents of this words element) here we should consider that 
						until fds are sorted evberything is waiting on that. 
					if check keyword
						do keyword on fd or on next word
					else
						execve with word
				}
				if pipe
				sort out frist element with if simple
					duplicate the output to the input of the next element
						check keyword, if yes, do keyword on fd or on next word
						else execve with word to dup2 stdout
				i++;
			}

		check redirection / do  redirection 
			if strchr < or << 
				get file to the right or token and cat? it to the fd of left file.
				repeat until no strchr < or <<
			else if only one token cat to fd of right file.
			if more tokens then RESEARCH BEHAVIOR OF BASH.

*/
int	piperino6(t_words **INstruct)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
    int		i;

    i = 0;
    pipe_fd = malloc(200 * sizeof(int *));
    while (is_pipe(INstruct, i))
    {
        pipe_fd[i] = malloc(2 * sizeof(int));
        if (pipe(pipe_fd[i]) == -1)
            error_exit("(piperino6) Pipe creation failed\n");
        i++;
    }
    i = 0;
    while (INstruct[i] != NULL)
    {
        cmd1 = ft_split(INstruct[i]->word_clean, ' ');
        path1 = ft_strjoin("/bin/", cmd1[0]);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            if (is_pipe(INstruct, i))
            {
                dup2(pipe_fd[i][1], STDOUT_FILENO);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
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
        free_piperino2(INstruct[i], cmd1, path1);
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (is_pipe(INstruct, j))
        {
            close(pipe_fd[j][1]);
        }
    }

    for (int j = 0; j < i; j++)
    {
        waitpid(pids[j], NULL, 0);
	}

    return (i);
}
int piperino5(t_words **INstruct)
{
	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
	int		pipe_fd[2];
	int		tmp_read_fd;
	pid_t	pid;

	int	i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	{
		if (pipe(pipe_fd) == -1)
			error_exit("(piperino5) Pipe creation failed\n");
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			if (i != 0)
			{
				dup2(tmp_read_fd, STDIN_FILENO);
				close(tmp_read_fd);
			}
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execve(path1, cmd1, NULL);
			perror("(piperino5) Exec1 failed");
		}
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		free_piperino(cmd1, path1);
		i++;
		cmd1 = ft_split(INstruct[i]->word_clean, ' ');
		path1 = ft_strjoin("/bin/", cmd1[0]);
		tmp_read_fd = pipe_fd[0];
	}
	// for (int i; i < 2; i++)
	// 	waitpid(-1, NULL, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(tmp_read_fd, STDIN_FILENO);
		close(tmp_read_fd);
		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	close(tmp_read_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	free_piperino(cmd1, path1);
	return (i);
}

void	routine(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->INstruct[0]->num_of_elements)
	{
		if (data->INstruct[i]->token_after_word != NULL && \
				data->INstruct[i]->token_after_word[0] == '|')
			i += piperino6(&data->INstruct[i]);
		else
			parser(data,i);
		i++;
	}
}

int	parser(t_data *data,int i)
{
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
	//still have to handle
		exit(EXIT_SUCCESS);
	else
		executor(data->INstruct[i]->word_clean, data);
	return (0);
}

/*
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

void	skip_prespaces(char **str)
{
	while (*(str[0]) == ' ')
		(*str)++; 
}

char	*clean_spaces(char *word)
{
	char	*tmp_word;

	skip_prespaces(&word); /// macht das sinn?... 
	word = ft_strdup(word); //FREE // WTF
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



int	piperino8(t_words **INstruct, int i)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
	int		j;

    j = i;
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
        cmd1 = ft_split(INstruct[i]->word_clean, ' ');
        path1 = ft_strjoin("/bin/", cmd1[0]);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            if (is_pipe(INstruct, i))
            {
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
        free_piperino2(INstruct[i], cmd1, path1);
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

int Executor2(t_data *data)
{
	int	i = 0;

	while (i < data->INstruct[0]->num_of_elements)
	{
		// if (is_redirection)
		// {
				// i += redirectionprog(INstruct, i)
		// }
		// printf("rcmd:%s\n", data->INstruct[i]->redirection->whole_command);
		// if (data->INstruct[i]->redirection->whole_command[3] == '<') // <
		// {
		// 	data->INstruct[i]->redirection->fd_in = open("file", O_RDONLY);	
		// 	dup2(data->INstruct[i]->redirection->fd_in, STDIN_FILENO);
		// }
		if (is_pipe(data->INstruct, i))
		{
			i += piperino8(data->INstruct, i);
		}
		else
			single_command(data, i);
		i++;
	}
	return (i);
}
int	piperino6(t_words **INstruct)
{
    char	**cmd1;
    char	*path1;
    int		**pipe_fd;
    pid_t	pids[100];
    int		i;

    i = 0;
    pipe_fd = malloc(200 * sizeof(int *));
    while (is_pipe(INstruct, i))
    {
        pipe_fd[i] = malloc(2 * sizeof(int));
        if (pipe(pipe_fd[i]) == -1)
            error_exit("(piperino6) Pipe creation failed\n");
        i++;
    }
    i = 0;
    while (INstruct[i] != NULL)
    {
        cmd1 = ft_split(INstruct[i]->word_clean, ' ');
        path1 = ft_strjoin("/bin/", cmd1[0]);
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i != 0)
            {
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            if (is_pipe(INstruct, i))
            {
                dup2(pipe_fd[i][1], STDOUT_FILENO);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
			int j = i;
			while (is_pipe(INstruct, j))
			{
                close(pipe_fd[j][0]);
                close(pipe_fd[j][1]);	
				j++;		
			}

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
        free_piperino2(INstruct[i], cmd1, path1);
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (is_pipe(INstruct, j))
        {
            close(pipe_fd[j][1]);
        }
    }

    for (int j = 0; j < i; j++)
    {
        waitpid(pids[j], NULL, 0);
	}

    return (i);
}
int piperino5(t_words **INstruct)
{
	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
	int		pipe_fd[2];
	int		tmp_read_fd;
	pid_t	pid;

	int	i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	{
		if (pipe(pipe_fd) == -1)
			error_exit("(piperino5) Pipe creation failed\n");
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			if (i != 0)
			{
				dup2(tmp_read_fd, STDIN_FILENO);
				close(tmp_read_fd);
			}
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execve(path1, cmd1, NULL);
			perror("(piperino5) Exec1 failed");
		}
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		free_piperino(cmd1, path1);
		i++;
		cmd1 = ft_split(INstruct[i]->word_clean, ' ');
		path1 = ft_strjoin("/bin/", cmd1[0]);
		tmp_read_fd = pipe_fd[0];
	}
	// for (int i; i < 2; i++)
	// 	waitpid(-1, NULL, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(tmp_read_fd, STDIN_FILENO);
		close(tmp_read_fd);
		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	close(tmp_read_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	free_piperino(cmd1, path1);
	return (i);
}

void	routine(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->INstruct[0]->num_of_elements)
	{
		if (data->INstruct[i]->token_after_word != NULL && \
				data->INstruct[i]->token_after_word[0] == '|')
			i += piperino6(&data->INstruct[i]);
		else
			single_command(data,i);
		i++;
	}
}

int	single_command(t_data *data,int i)
{
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
	//still have to handle
		exit(EXIT_SUCCESS);
	else
		executor(data->INstruct[i]->word_clean, data->envp);
	return (0);
}

*/