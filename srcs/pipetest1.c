#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// void	executor(char *clean_word, char **envp)
// {
// 	int pid;
// 	(void)envp;
// 	char	**args = ft_split(clean_word, ' ');

// 	printf("->%s\n", clean_word);
// 	if ((pid = fork()) == -1)
// 	perror("fork error");
// 	else if (pid == 0) 
// 	{
// 		execve(ft_strjoin("/bin/",args[0]), args, NULL);
// 		printf("Return not expected. Must be an execve error.\n");
// 	}
// 	else
// 		waitpid(0, NULL, 0);
// }

// int	main(int argc, char**argv)
int	main()
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		printf("Pipeerstellung Fehlgeschlagen!\n");
		exit(EXIT_FAILURE);
	}
	// close(pipe_fd[0]);
	// close(pipe_fd[1]);

	pid_t	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed!\n");
		exit(EXIT_FAILURE);
	}	

	if (pid == 0)
	{
        close(pipe_fd[0]); // Das Lesende Ende wird nicht benötigt

		// open(pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		printf("HALLIHALLO\n");
        // dprintf(pipe_fd[1], "Hallo von Kindprozess!\n");

		// printf("ChildSTDOUT_FILENO:%d\n", STDOUT_FILENO);
		close(pipe_fd[1]);
		
	}
	else
	{
		// Elternprozess
		close(pipe_fd[1]); // Das Schreibende Ende wird nicht benötigt

		// Lies Daten vom Lesenden Ende der Pipe
		char buffer[100];
		ssize_t bytesRead = read(pipe_fd[0], buffer, sizeof(buffer));
		close(pipe_fd[0]); // Schließe das Lesende Ende nach dem Lesen

		if (bytesRead > 0) {
			buffer[bytesRead] = '\0'; // Füge Nullterminator für printf hinzu
			printf("Elternprozess hat gelesen: %s", buffer);
		} else {
			printf("Lesen fehlgeschlagen!\n");
		}
	}
		// printf("ParentSTDOUT_FILENO:%d\n", STDOUT_FILENO);

	waitpid(pid, NULL, 0);

	return (0);
}

