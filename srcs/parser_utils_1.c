#include "minishell.h"



// char	*echo(char *word)
// {
// 	char	**words;
// 	// bool	flag;

// 	// flag = false;
// 	// printf("ECHO\n");

// 	words = ft_split(word, ' ');

// 	int i = 0;
// 	while (words[i] != NULL)
// 	{
// 		printf("%i|", i);

// 		printf("%s", words[i++]);
// 		printf("|\n");
// 	}
// 	return (NULL);
// }

char	*echo(char *word)
{
	bool	flag;
	// printf("word|%s|\n", word);
	flag = false;
	word += 5;
	while (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	if (flag)
		return (ft_savef("%s", word));
	return (ft_savef("%s\n", word));
}

char	*getpwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd() error");
		return (NULL);
	}
	return (buf);
}

int	cd(char *dir)
{
	if (dir[2] == ' ')
		dir += 3;
	// if (dir[])
    if (chdir(dir) != 0) 
    {
        perror("(cd) No valid pathname!");
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

int	ls(char *dir)
{
	pid_t p = fork();

	if(p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	// if (p == 0)
	// {
	// 	char *ls_argv[] = {"ls", dir, NULL};

	// 	if (execve("/bin/ls", ls_argv, NULL) == -1)
	// 		perror("(ls) Fehler bei execve\n");
	// 	exit(0);
	// }
	if (p == 0) { // Dieser Code wird nur im Kindprozess ausgeführt
		char *ls_argv[] = {"ls", dir, NULL};
		execv("/bin/ls", ls_argv);
		perror("execv failed");
		exit(1);
	}
	return 0;
}

// int	ls(char *dir) {
// 	pid_t p = fork();

// 	if(p < 0)
// 	{
// 		perror("fork fail");
// 		exit(1);
// 	}
// 	if (p == 0)
// 	{
// 		printf("Hello world!, process_id(pid) = %d \n",getpid());
// 		exit(0);
// 	}
// 	return 0;
// }

    // printf("Hello world!, process_id(pid) = %d \n",getpid());

	// char *ls_argv[] = {"ls", dir, NULL};
	// if (execve("/bin/ls", ls_argv, NULL) == -1) {
	//     perror("Fehler bei execve");
	//     return 1;
	// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <unistd.h>

// int main(int argc, char *argv[]) {
//     // Überprüfen, ob das Verzeichnis als Argument angegeben wurde
//     if (argc != 2) {
//         fprintf(stderr, "Verwendung: %s <Verzeichnis>\n", argv[0]);
//         return 1;
//     }

//     const char *directory = argv[1];
//     struct dirent *entry;
//     DIR *dir;

//     // Öffnen des Verzeichnisses
//     dir = opendir(directory);
//     if (dir == NULL) {
//         perror("Fehler beim Öffnen des Verzeichnisses");
//         return 1;
//     }

//     // Schleife zum Lesen und Anzeigen der Verzeichniseinträge
//     while ((entry = readdir(dir)) != NULL) {
//         printf("%s\n", entry->d_name);
//     }

//     // Verzeichnis schließen
//     closedir(dir);

//     // Verwenden von execve, um ls im Verzeichnis aufzurufen
//     char *ls_argv[] = {"ls", directory, NULL};
//     if (execve("/bin/ls", ls_argv, NULL) == -1) {
//         perror("Fehler bei execve");
//         return 1;
//     }

//     return 0;
// }
