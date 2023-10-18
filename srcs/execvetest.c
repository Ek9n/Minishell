#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Überprüfen, ob das Verzeichnis als Argument angegeben wurde
    if (argc != 2) {
        fprintf(stderr, "Verwendung: %s <Verzeichnis>\n", argv[0]);
        return 1;
    }

    char *directory = argv[1];
    
    // Verwenden von execve, um ls im Verzeichnis aufzurufen
    char *ls_argv[] = {"ls", directory, NULL};
    if (execve("/bin/ls", ls_argv, NULL) == -1) {
        perror("Fehler bei execve");
        return 1;
    }

    return 0;
}
