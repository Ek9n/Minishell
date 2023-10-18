#include "parser.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;
	
	n = ft_strlen(s1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

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
	printf("try:%s\n", dir);
	if (dir[2] == ' ')
		dir += 3;
	printf("try:%s\n", dir);
	// if (dir[])
    if (chdir(dir) != 0) 
    {
        perror("(cd) No valid pathname!");
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

int	ls(char *dir) {
    // Verwenden von execve, um ls im Verzeichnis aufzurufen
    char *ls_argv[] = {"ls", dir, NULL};
    if (execve("/bin/ls", ls_argv, NULL) == -1) {
        perror("Fehler bei execve");
        return 1;
    }
    return 0;
}

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
