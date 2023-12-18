#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	pid = fork();

	if (pid == 0)
	{
		close(pipe_fd[0]);
		char	str[] = "HALLO\n";
		write(pipe_fd[1], str, 6);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
	static char	buffer[100];
	read(pipe_fd[0], buffer, 50);
	printf("%s", buffer);
	return (0);
}
