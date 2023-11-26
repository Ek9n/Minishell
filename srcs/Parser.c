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
	// while (**str == ' ')
	while (*(str[0]) == ' ')
		(*str)++; // Inkrementiere den Zeiger auf die Zeichenkette, um Leerzeichen zu überspringen
}

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


// int piperino6(t_words **INstruct)
// {
// 	char	**cmd1;
// 	char	*path1;
// 	int		**pipe_fd;
// 	int		pids[100];
// 	pid_t	pid;

// 	pipe_fd = malloc(200 * sizeof(int*));
// 	for (int j = 0; j < 3; j++)
// 	{
// 		pipe_fd[j] = malloc(2 * sizeof(int));
// 		if (pipe(pipe_fd[j]) == -1)
// 			error_exit("(piperino5) Pipe creation failed\n");
// 	}
// 	int	i = 0;
// 	// while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
// 	while (INstruct[i] != NULL)
// 	{
// 		cmd1 = ft_split(INstruct[i]->word_clean, ' ');
// 		path1 = ft_strjoin("/bin/", cmd1[0]);
// 		pids[i] = fork();
// 		if (pids[i] == 0)
// 		{
// 			if (i == 0)
// 			{
// 				close(pipe_fd[i][0]);
// 				dup2(pipe_fd[i][1], STDOUT_FILENO);
// 				close(pipe_fd[i][1]);
// 			}
// 			else if (INstruct[i]->token_after_word != NULL)
// 			{
// 				close(pipe_fd[i][0]);
// 				dup2(pipe_fd[i-1][0], STDIN_FILENO);
// 				close(pipe_fd[i-1][0]);
// 				dup2(pipe_fd[i][1], STDOUT_FILENO);
// 				close(pipe_fd[i][1]);
// 			}
// 			else
// 			{
// 				dup2(pipe_fd[i-1][0], STDIN_FILENO);
// 				close(pipe_fd[i-1][0]);
// 			}
// 			execve(path1, cmd1, NULL);
// 			perror("(piperino5) Exec1 failed");
// 		}
// 		// printf("hi[%d\n", i);

// 		if (INstruct[i+1] != NULL) // wenn man das nicht macht, kann man am ende mit str+d nicht beenden..
// 			close(pipe_fd[i][1]);
		
// 		// if (i != 0)
// 		// 	close(pipe_fd[i-1][0]);
// 		free_piperino2(INstruct[i], cmd1, path1);
// 		i++;
// 	}
// 	for (int j = 0; j < 3; j++) {
// 		close(pipe_fd[j][0]);
// 		// close(pipe_fd[j][1]);
// 		// free(pipe_fd[j]);
// 	}
// 	// free(pipe_fd);
// 	// waitpid(-1, NULL, 0);
// 	// for (int i = 0; i < 4; i++)
// 	// 	kill(pids[i], SIGTERM);
// 	for (int i = 0; i < 4; i++)
// 		waitpid(pids[i], NULL, 0);
// 	// printf("shieet\n");
// 	return (i);
// }

int	cnt_pipes(t_words **INstruct)
{
	int	 i;

	i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
		i++;
	return (i);
}


int piperino7(t_words **INstruct)
{
	char	**cmd1;
	char	*path1;
	int		**pipe_fd;
	int		pids[100];
	pid_t	pid;

	pipe_fd = malloc(200 * sizeof(int*));
	for (int j = 0; j < 3; j++)
	{
		pipe_fd[j] = malloc(2 * sizeof(int));
		if (pipe(pipe_fd[j]) == -1)
			error_exit("(piperino5) Pipe creation failed\n");
		printf("pipe[%d]:read=%d, write=%d\n", j, pipe_fd[j][0], pipe_fd[j][1]);
	}

	cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	path1 = ft_strjoin("/bin/", cmd1[0]);
	pid = fork();
	if (pid == 0)
	{
		printf("Start:\n");
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);

		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	// free_piperino2(INstruct[i], cmd1, path1);
	cmd1 = ft_split(INstruct[1]->word_clean, ' ');
	path1 = ft_strjoin("/bin/", cmd1[0]);
	pid = fork();
	if (pid == 0)
	{
		printf("Mid:\n");
		dup2(pipe_fd[0][0], STDIN_FILENO);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		dup2(pipe_fd[1][1], STDOUT_FILENO);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);

		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	// free_piperino2(INstruct[i], cmd1, path1);
	cmd1 = ft_split(INstruct[2]->word_clean, ' ');
	path1 = ft_strjoin("/bin/", cmd1[0]);
	pid = fork();
	if (pid == 0)
	{
		printf("End:\n");
		dup2(pipe_fd[1][0], STDIN_FILENO);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);

		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	// free_piperino2(INstruct[i], cmd1, path1);
	int i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		printf("closeread=%d\n", pipe_fd[i][0]);
		printf("closewrite=%d\n", pipe_fd[i][1]);
		i++;
		// free(pipe_fd[j]);
	}
	// close(pipe_fd[i][0]);
	// close(pipe_fd[i][1]);
	// printf("closeread=%d\n", pipe_fd[i][0]);
	// printf("closewrite=%d\n", pipe_fd[i][1]);
	// free(pipe_fd);
	// kill(pid_to_kill, SIGTERM);
	for (int i = 0; i < 3; i++)
		waitpid(-1, NULL, 0);
	// printf("shieet\n");
	return (i);
}


int piperino6(t_words **INstruct)
{
	char	**cmd1;
	char	*path1;
	int		**pipe_fd;
	int		pids[100];
	pid_t	pid;

	pipe_fd = malloc(200 * sizeof(int*));
	for (int j = 0; j < 3; j++)
	{
		pipe_fd[j] = malloc(2 * sizeof(int));
		if (pipe(pipe_fd[j]) == -1)
			error_exit("(piperino5) Pipe creation failed\n");
		printf("pipe[%d]:read=%d, write=%d\n", j, pipe_fd[j][0], pipe_fd[j][1]);
	}
	int	i = 0;
	// while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	while (INstruct[i] != NULL)
	{
		cmd1 = ft_split(INstruct[i]->word_clean, ' ');
		path1 = ft_strjoin("/bin/", cmd1[0]);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				printf("Start:\n");
				dup2(pipe_fd[i][1], STDOUT_FILENO);
				close(pipe_fd[i][0]);
				close(pipe_fd[i][1]);
			}
			else if (INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
			{
				printf("Mid:\n");
				dup2(pipe_fd[i-1][0], STDIN_FILENO);
				close(pipe_fd[i-1][0]);
				close(pipe_fd[i-1][1]);
				dup2(pipe_fd[i][1], STDOUT_FILENO);
				close(pipe_fd[i][0]);
				close(pipe_fd[i][1]);
			}
			else
			{
				printf("End:\n");
				dup2(pipe_fd[i-1][0], STDIN_FILENO);
				close(pipe_fd[i-1][0]);
				close(pipe_fd[i-1][1]);
			}
			execve(path1, cmd1, NULL);
			perror("(piperino5) Exec1 failed");
		}
		// printf("hi[%d\n", i);

		// if (INstruct[i+1] != NULL) // wenn man das nicht macht, kann man am ende mit str+d nicht beenden..
			// close(pipe_fd[i][1]);
		
		// if (i != 0)
		// 	close(pipe_fd[i-1][0]);
		free_piperino2(INstruct[i], cmd1, path1);
		i++;
	}
	i = 0;
	while (INstruct[i+1] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		printf("closeread=%d\n", pipe_fd[i][0]);
		printf("closewrite=%d\n", pipe_fd[i][1]);
		i++;
		// free(pipe_fd[j]);
	}
	close(pipe_fd[i][0]);
	close(pipe_fd[i][1]);
	printf("closeread=%d\n", pipe_fd[i][0]);
	printf("closewrite=%d\n", pipe_fd[i][1]);
	// free(pipe_fd);
	// kill(pid_to_kill, SIGTERM);
	for (int i = 0; i < 4; i++)
		waitpid(-1, NULL, 0);
	// printf("shieet\n");
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

void	routine(t_words **INstruct)
{
	int	i;
	// printf("elements:%d\n", INstruct[0]->num_of_elements);
	clean_words(INstruct);
	i = 0;
	while (i < INstruct[0]->num_of_elements)
	{
		if (INstruct[i]->token_after_word != NULL && \
				INstruct[i]->token_after_word[0] == '|')
			i += piperino5(&INstruct[i]);
		else
			parser(INstruct[i]);
		i++;
	}
}

int	parser(t_words *INstruct)
{
	if (cmp_keyword("echo", INstruct->word_clean))
	{
		INstruct->output = echo(INstruct->word_clean);
		printf("%s", INstruct->output);
	}
	else if (cmp_keyword("pwd", INstruct->word_clean))
	{
		INstruct->output = getpwd();
		printf("%s\n", INstruct->output);
	}
	else if (cmp_keyword("cd", INstruct->word_clean))
	{
		cd(INstruct->word_clean);
	}
	else
		executor(INstruct->word_clean, INstruct->enviroment);
	return (0);
}
