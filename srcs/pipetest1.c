#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// int	main(int argc, char**argv)
int	main()
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		printf("Pipeerstellung Fehlgeschlagen!\n");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	pid_t	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed!\n");
		exit(EXIT_FAILURE);
	}	

	if (pid == 0)
	{

	}

	return (0);
}

// void error_exit(char *msg) {
//     perror(msg);
//     exit(EXIT_FAILURE);
// }

// int main(int argc, char *argv[]) {
//     if (argc != 5) {
//         fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }

//     char *file1 = argv[1];
//     char *cmd1 = argv[2];
//     char *cmd2 = argv[3];
//     char *file2 = argv[4];

//     int pipe_fd[2];

//     // Erzeuge die Pipe
//     if (pipe(pipe_fd) == -1) {
//         error_exit("Pipe creation failed");
//     }

//     // Fork den ersten Kindprozess
//     pid_t pid1 = fork();
//     if (pid1 == -1) {
//         error_exit("Fork failed");
//     }

//     if (pid1 == 0) {
//         // Im ersten Kindprozess
//         // Schließe das Schreibende Ende der Pipe
//         close(pipe_fd[0]);

//         // Leite die Standardausgabe zum Schreibende der Pipe um
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[1]);

//         // Führe das erste Programm aus
//         execlp(cmd1, cmd1, file1, NULL);
//         error_exit("Exec failed for cmd1");
//     }

//     // Fork den zweiten Kindprozess
//     pid_t pid2 = fork();
//     if (pid2 == -1) {
//         error_exit("Fork failed");
//     }

//     if (pid2 == 0) {
//         // Im zweiten Kindprozess
//         // Schließe das Lesende Ende der Pipe
//         close(pipe_fd[1]);

//         // Leite die Standard­eingebe vom Lesende der Pipe um
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[0]);

//         // Führe das zweite Programm aus
//         execlp(cmd2, cmd2, file2, NULL);
//         error_exit("Exec failed for cmd2");
//     }

//     // Im Elternprozess
//     // Schließe beide Enden der Pipe
//     close(pipe_fd[0]);
//     close(pipe_fd[1]);

//     // Warte auf die Beendigung beider Kindprozesse
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);

//     return 0;
// }