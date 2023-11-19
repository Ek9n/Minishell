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
		// (*str)++; // Inkrementiere den Zeiger auf die Zeichenkette, um Leerzeichen zu überspringen
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

static void	free_piperino(char **cmd1, char **cmd2, char *path1, char *path2)
{
	int	i;

	i = 0;
	while(cmd1[i] != NULL)
		free(cmd1[i++]);
	free(cmd1);
	i = 0;
	while(cmd2[i] != NULL)
		free(cmd2[i++]);
	free(cmd2);	
	free(path1);
	free(path2);
}

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	free_piperino2(char **cmd1, char *path1)
{
	int	i;

	i = 0;
	while(cmd1[i] != NULL)
		free(cmd1[i++]);
	free(cmd1);
	free(path1);
}

void	printpipe(int read_fd)
{
	char	buffer[999];
	read(read_fd, buffer, 10);
	printf("%s\n", buffer);
}

int piperino5(t_words **INstruct)
{
	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
	int		pipe_fd[2];
	int		tmp_read_fd;
	pid_t	pid;

	int	i = 0;
	while (INstruct[i] != NULL && INstruct[i]->token_after_word != NULL && INstruct[i]->token_after_word[0] == '|')
	{
		if (pipe(pipe_fd) == -1)
			error_exit("(piperino5) Pipe creation failed\n");
		if (i == 0)
			tmp_read_fd = pipe_fd[0];
		pid = fork();

		if (pid == 0)
		{
			if (i == 0)
				close(pipe_fd[0]);
			else
				dup2(tmp_read_fd, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execve(path1, cmd1, NULL);
			perror("(piperino5) Exec1 failed");
		}
		close(pipe_fd[1]);
		printf("Angekommen1\n");
		// waitpid(-1, NULL, WUNTRACED);
		waitpid(pid, NULL, 0);
		printf("Angekommen2[%d]\n", i);
		i++;
		free_piperino2(cmd1, path1);
		cmd1 = ft_split(INstruct[i]->word_clean, ' '); //free nicht vergessen
		path1 = ft_strjoin("/bin/", cmd1[0]);
		// close(tmp_read_fd); // wenn man hier schliesst gibts probleme.. warum? .. er wartet dann... glaub wegen spaeteren fork..der nimmt dann die geschlossene pipe mit
		tmp_read_fd = pipe_fd[0];
	}
	pid = fork();
	if (pid == 0)
	{
		printf("AngekommeX\n");
		dup2(tmp_read_fd, STDIN_FILENO);
		close(tmp_read_fd);
		printf("AngekommeY\n");
		execve(path1, cmd1, NULL);
		perror("(piperino5) Exec1 failed");
	}
	close(tmp_read_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
		// printf("AngekommeY\n");
	// waitpid(-1, NULL, WUNTRACED);
	// waitpid(pid, NULL, 0);
		// printf("AngekommeZ\n");
	free_piperino2(cmd1, path1);
	return (0);
}

int piperino3(t_words **INstruct, int pipe_read) {
	char **cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char *path1 = ft_strjoin("/bin/", cmd1[0]);

	pid_t pid = fork();
	if (pid == -1)
		error_exit("(piperino3) Fork failed\n");
	if (pid == 0) {
		if (dup2(pipe_read, STDIN_FILENO) == -1)
			error_exit("dup2 for stdin failed");

		execve(path1, cmd1, NULL);
		perror("(piperino3) Exec1 failed");
		exit(EXIT_FAILURE);
	} else {
		close(pipe_read);
		free_piperino2(cmd1, path1);
	}
	return 0;
}

int piperino4(t_words **INstruct, int pipe_read)
{
	char **cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char *path1 = ft_strjoin("/bin/", cmd1[0]);

	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
		error_exit("(piperino1) Pipe creation failed\n");
	pid_t pid = fork();
	if (pid == -1)
		error_exit("(piperino3) Fork failed\n");

	if (pid == 0)
	{
		if (pipe_read != -1)
			if (dup2(pipe_read, STDIN_FILENO) == -1)
				error_exit("dup2 for stdin failed");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 for stdout failed");
		execve(path1, cmd1, NULL);
		perror("(piperino3) Exec1 failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_read);
		waitpid(pid, NULL, 0);

		if (INstruct[1]->token_after_word != NULL && INstruct[1]->token_after_word[0] == '|')
			piperino4(&INstruct[1], pipe_fd[0]);
		else
			piperino3(&INstruct[1], pipe_fd[0]);
		free_piperino2(cmd1, path1);
	}
	return 0;
}



int piperino2(t_words **INstruct, int pipe_read)
{
	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
	int 	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error_exit("(piperino2) Pipe creation failed\n");

	// close(pipe_fd[0]);
	pid_t pid = fork();
	if (pid == -1)
		error_exit("(piperino2) Fork failed\n");
	if (pid == 0)
	{

		if (dup2(pipe_read, STDIN_FILENO) == -1)
			error_exit("dup2 for stdin failed");
		printf("before2:%d\n", pipe_fd[1]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 for stdout failed");
		printf("after\n");
		// close(pipe_read);

		// close(pipe_fd[1]);

		execve(path1, cmd1, NULL);
		perror("(piperino2) Exec1 failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		// close(pipe_read);
		// close(pipe_fd[1]);
		// close(pipe_fd[0]);
		printf("kommt bis hier\n");
		waitpid(pid, NULL, 0);
		printf("kommt nciht bis hier\n");
		// piperino3(&INstruct[1], pipe_fd[0]);
		free_piperino2(cmd1, path1);
	}
	return 0;
}

int piperino1(t_words **INstruct) {
	char **cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char *path1 = ft_strjoin("/bin/", cmd1[0]);
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error_exit("(piperino1) Pipe creation failed\n");

	pid_t pid = fork();
	if (pid == -1)
		error_exit("(piperino1) Fork failed\n");
	if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 for stdout failed");

		close(pipe_fd[0]);
		execve(path1, cmd1, NULL);
		perror("(piperino1) Exec1 failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (INstruct[1]->token_after_word != NULL && INstruct[1]->token_after_word[0] == '|')
			piperino2(&INstruct[1], pipe_fd[0]);
		else
			piperino3(&INstruct[1], pipe_fd[0]);

		close(pipe_fd[0]);
		close(pipe_fd[1]);
		printf("kommt bis hier\n");
		waitpid(pid, NULL, 0);
		printf("kommt nciht bis hier\n");
		free_piperino2(cmd1, path1);
	}
	return 0;
}


// int	piperino3(t_words **INstruct, int pipe_read) //may it should be a pointer
// {
// 	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
// 	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
// 	// printf("INstruct[0]->word_clean[0]=%c\n", INstruct[0]->word_clean[0]);

// 	pid_t	pid = fork();
// 	if (pid == -1)
// 		error_exit("(piperino3) Fork failed\n");
// 	if (pid == 0)
// 	{
// 		if (dup2(pipe_read, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 for stdin failed");
// 			fprintf(stderr, "Error details: %s\n", strerror(errno));
// 			exit(EXIT_FAILURE);
// 		}
// 		// close(pipe_read);
// 		execve(path1, cmd1, NULL);
// 		error_exit("(piperino3) Exec1 failed");
// 	}
// 	else
// 	{
// 		// waitpid(pid, NULL, 0); //soll er ueberhaupt warten?
// 		// printf("SACJ!\n");
// 		close(pipe_read);
// 		free_piperino2(cmd1, path1);
// 	}
// 	return (0);
// }


// int piperino2(t_words **INstruct, int pipe_read) {
//     char **cmd1 = ft_split(INstruct[0]->word_clean, ' ');
//     char *path1 = ft_strjoin("/bin/", cmd1[0]);
//     int pipe_fd[2];

//     // Erzeuge die Pipe
//     if (pipe(pipe_fd) == -1)
//         error_exit("(piperino2) Pipe creation failed\n");

//     pid_t pid = fork();
//     if (pid == -1)
//         error_exit("(piperino2) Fork failed\n");
//     if (pid == 0) {
//         // Kindprozess
//         if (dup2(pipe_read, STDIN_FILENO) == -1)
//             error_exit("dup2 for stdin failed");

//         if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
//             error_exit("dup2 for stdout failed");

//         // Schließe unbenutzte Pipe-Enden
//         close(pipe_read);
//         close(pipe_fd[0]);
//         // close(pipe_fd[1]);

//         // Führe den Befehl im Kindprozess aus
//         execve(path1, cmd1, NULL);
//         // Falls execve fehlschlägt, gibt es eine Fehlermeldung aus
//         perror("(piperino2) Exec1 failed");
//         exit(EXIT_FAILURE);
//     } else {
//         // Elternprozess
//         close(pipe_fd[1]);  // Schließe das Schreibende Ende der Pipe im Elternprozess

//         waitpid(pid, NULL, 0);  // Warte auf den Kindprozess

//         // Hier kannst du weitere Aktionen im Elternprozess durchführen,
//         // z.B. das Weiterverarbeiten von Daten aus der Pipe oder das Starten eines weiteren Kindprozesses
//         piperino3(&INstruct[0], pipe_fd[0]);

//         // Schließe das Lesende Ende der Pipe im Elternprozess
//         close(pipe_fd[0]);

//         // Freigabe von Speicher, falls erforderlich
//         free_piperino2(cmd1, path1);
//     }
//     return 0;
// }

// int	piperino1(t_words **INstruct)
// {
// 	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
// 	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
// 	int		pipe_fd[2];

// 	// Erzeuge die Pipe
// 	if (pipe(pipe_fd) == -1)
// 		error_exit("(piperino1) Pipe creation failed\n");
// 	pid_t	pid = fork();
// 	if (pid == -1)
// 		error_exit("(piperino1) Fork failed\n");
// 	if (pid == 0)
// 	{
// 		// close(pipe_fd[0]); 
// 		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 for stdout failed");
// 			fprintf(stderr, "Error details: %s\n", strerror(errno));
// 			exit(EXIT_FAILURE);
// 		}
// 		// close(pipe_fd[1]);??
// 		execve(path1, cmd1, NULL);
// 		error_exit("(piperino1) Exec1 failed");
// 	}
// 	else
// 	{
// 		if (INstruct[1]->token_after_word != NULL)
// 		{
// 			if (INstruct[1]->token_after_word[0] == '|')
// 				piperino2(&INstruct[1], pipe_fd[0]);
// 		}
// 		else
// 			piperino3(&INstruct[1], pipe_fd[0]); // 3
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		waitpid(pid, NULL, 0); //soll er ueberhaupt warten?
// 		free_piperino2(cmd1, path1);
// 		// printf("ALARM1!\n");
// 	}
// 	return (0);
// }

// int	piperino(t_words **INstruct, char *cmd1, char *cmd2)
int	piperino(t_words **INstruct)
{
	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
	char	**cmd2 = ft_split(INstruct[1]->word_clean, ' '); 
	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
	char	*path2 = ft_strjoin("/bin/", cmd2[0]);
	int		pipe_fd[2];

	// Erzeuge die Pipe
	if (pipe(pipe_fd) == -1)
		error_exit("(piperino) Pipe creation failed\n");

	pid_t	pid_cat = fork();
	if (pid_cat == -1)
		error_exit("(piperino) Fork failed\n");

	if (pid_cat == 0)
	{
		close(pipe_fd[0]); 
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 for stdout failed");
			fprintf(stderr, "Error details: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
		execve(path1, cmd1, NULL);
		error_exit("(piperino) Exec1 failed");
	}
	else
	{
		close(pipe_fd[1]);
		pid_t pid_wc = fork();
		if (pid_wc == -1) 
		{
			error_exit("Fork failed");
		}
		if (pid_wc == 0)
		{	
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);

			// if (INstruct[1]->token_after_word != NULL)
			// {
				// if (INstruct[1]->token_after_word[0] == '|')
				// {
				// 	int	pipe_fd2[2];

				// 	if (pipe(pipe_fd2) == -1)
				// 		error_exit("(piperino) Pipe(2) creation failed\n");
				// 	close(pipe_fd2[0]); // ???
				// 	dup2(pipe_fd2[1], STDOUT_FILENO);
				// 	piperino(&INstruct[1]);

				// 	// piperino2(&INstruct[1], pipe_fd2[0]);

				// 	// dup2(pipe_fd2[1], STDOUT_FILENO);
				// 	// execve(path2, cmd2, NULL);
				// 	// error_exit("(piperino) Exec2 failed");
					
				// }
				// else
				// {
					execve(path2, cmd2, NULL);
					error_exit("(piperino) Exec2 failed");
				// }
			// }
		}
		else {
			close(pipe_fd[0]); 
			// printf("Jo1\n");
			waitpid(pid_cat, NULL, 0);
			// printf("Jo2\n");
			waitpid(pid_wc, NULL, 0);
			// printf("Jo3\n");

		}
	}
	free_piperino(cmd1, cmd2, path1, path2);
	// printf("Jo4\n");
	return (0);
}

// int	piperino2(t_words **INstruct, int pipe_fd[2])
// {
// 	char	**cmd1 = ft_split(INstruct[0]->word_clean, ' ');
// 	// char	**cmd2 = ft_split(INstruct[1]->word_clean, ' '); 
// 	char	*path1 = ft_strjoin("/bin/", cmd1[0]);
// 	// char	*path2 = ft_strjoin("/bin/", cmd2[0]);
// 	int		pipe_fd[2];

// 	// Erzeuge die Pipe
// 	if (pipe(pipe_fd) == -1)
// 		error_exit("(piperino) Pipe creation failed\n");

// 	pid_t	pid_cat = fork();
// 	if (pid_cat == -1)
// 		error_exit("(piperino) Fork failed\n");

// 	if (pid_cat == 0)
// 	{
// 		close(pipe_fd[0]); 
// 		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 for stdout failed");
// 			fprintf(stderr, "Error details: %s\n", strerror(errno));
// 			exit(EXIT_FAILURE);
// 		}
// 		close(pipe_fd[1]);
// 		execve(path1, cmd1, NULL);
// 		error_exit("(piperino) Exec1 failed");
// 	}
// 	else
// 	{
// 		close(pipe_fd[1]);
// 		pid_t pid_wc = fork();
// 		if (pid_wc == -1) 
// 		{
// 			error_exit("Fork failed");
// 		}
// 		if (pid_wc == 0)
// 		{	
// 			dup2(pipe_fd[0], STDIN_FILENO);
// 			close(pipe_fd[0]);


// 			// if (INstruct[1]->token_after_word[0] == '|')
// 			// {
// 			// 	int	pipe_fd2[2];
// 			// 	if (pipe(pipe_fd) == -1)
// 			// 		error_exit("(piperino) Pipe(2) creation failed\n");
// 			// 	close(pipe_fd2[0]); // ???

// 			// 	piperino2(&INstruct[1], pipe_fd2[0]);

// 			// 	dup2(pipe_fd2[1], STDOUT_FILENO);
// 			// 	execve(path2, cmd2, NULL);
// 			// 	error_exit("(piperino) Exec2 failed");
				
// 			// }

// 			// if another pipe:
// 				//->new pipe -> dup2(pipe_fd[0], STDOUT_FILENO)
// 			// if (INstruct[1]->token_after_word[0] == '|')
// 			// {
// 			// 	int	pipe_fd2[2];
// 			// 	if (pipe(pipe_fd) == -1)
// 			// 		error_exit("(piperino) Pipe creation failed\n");
// 			//	close(pipe_fd2[0]); // ???
// 			// 	dup2(pipe_fd2[1], STDOUT_FILENO);
// 			//	execve(path2, cmd2, NULL);
// 			//	error_exit("(piperino) Exec2 failed");
// 			//	piperino2(&INstruct[1], pipe_fd2[0]); // der liesst aus der pipe und fuehrt cmd aus.. dann schaut er ob
// 			// noch eine ppe folgt.. wenn ja, fuehrt er wieder das gleiche spiel wie hier aus, ansonsten wird einfach in die stdausgabe geprintet... bzw.. in den output geschrieben...
// 			// }
// 			//else{....
// 			execve(path2, cmd2, NULL);
// 			error_exit("(piperino) Exec2 failed");
// 		}
// 		else {
// 			close(pipe_fd[0]); 
// 			// printf("Jo1\n");
// 			waitpid(pid_cat, NULL, 0);
// 			// printf("Jo2\n");
// 			waitpid(pid_wc, NULL, 0);
// 			// printf("Jo3\n");

// 		}
// 	}
// 	free_piperino(cmd1, cmd2, path1, path2);
// 	// printf("Jo4\n");
// 	return (0);
// }

void	routine(t_words **INstruct)
{
	int	i;
	// printf("elements:%d\n", INstruct[0]->num_of_elements);
	clean_words(INstruct);
	i = 0;
	while (i < INstruct[0]->num_of_elements)
	{
		// printf("fuck2\n");
		if (INstruct[i]->token_after_word != NULL)
		{
			if (INstruct[i]->token_after_word[0] == '|')
			{
				piperino5(&INstruct[i]);
				// printf("ALARM!\n");
				// piperino(&INstruct[i]);
			}
			i++;
		}
		else
			parser(INstruct[i]);
		i++;
		// printf("fuck1\n");
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

// int	parser(t_words **INstruct)
// {
// 	int	i;

// 	clean_words(INstruct);
// 	// printf("|%s|", INstruct[0]->word_clean);
// 	fflush(0);
// 	i = 0;
// 	while (i < INstruct[0]->num_of_elements)
// 	{
// 		if (cmp_keyword("echo", INstruct[i]->word_clean))
// 		{
// 			INstruct[i]->output = echo(INstruct[i]->word_clean);
// 			printf("%s", INstruct[i]->output);
// 		}
// 		else if (cmp_keyword("pwd", INstruct[i]->word_clean))
// 		{
// 			INstruct[i]->output = getpwd();
// 			printf("%s\n", INstruct[i]->output);
// 		}
// 		else if (cmp_keyword("cd", INstruct[i]->word_clean))
// 		{
// 			cd(INstruct[i]->word_clean);
// 		}
// 		else
// 			executor(INstruct[i]->word_clean, INstruct[i]->enviroment);
// 			// printf("(parser) could not find word\n");
// 		i++;
// 	}
// 	return (0);
// }