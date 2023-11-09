#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main() {
	int pipe_fd[2];

	// Erzeuge die Pipe
	if (pipe(pipe_fd) == -1)
		error_exit("Pipe creation failed");
	pid_t pid_cat = fork();
	if (pid_cat == -1)
		error_exit("Fork failed");
	if (pid_cat == 0)
	{
		// Kindprozess (cat)
		close(pipe_fd[0]); // Schließe das Lesende Ende der Pipe, da es nicht benötigt wird

		// Leite die Standardausgabe von cat zum Schreibenden Ende der Pipe um
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);

		// Ersetze den aktuellen Prozess durch cat
		char *cat_args[] = {"cat", "datei.txt", NULL};
		execve("/bin/cat", cat_args, NULL);
		error_exit("Exec failed for cat");
	}
	else
	{
		// Elternprozess
		close(pipe_fd[1]); // Schließe das Schreibende Ende der Pipe, da es nicht benötigt wird
		pid_t pid_wc = fork();
		if (pid_wc == -1) 
		{
			error_exit("Fork failed");
		}
		if (pid_wc == 0) {
			// Kindprozess (wc)
			// Leite die Standardeingabe von wc vom Lesenden Ende der Pipe um
			dup2(pipe_fd[0], STDIN_FILENO);

			// Ersetze den aktuellen Prozess durch wc
			char *wc_args[] = {"wc", "-l", NULL};
			execve("/usr/bin/wc", wc_args, NULL);
			close(pipe_fd[0]);
			error_exit("Exec failed for wc");
		}
		else {
			// Elternprozess
			close(pipe_fd[0]); // Schließe das Lesende Ende der Pipe, da es nicht benötigt wird

			// Warte auf das Ende beider Kindprozesse
			waitpid(pid_cat, NULL, 0);
			waitpid(pid_wc, NULL, 0);
		}
	}

	return 0;
}
