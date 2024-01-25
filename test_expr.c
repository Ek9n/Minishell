#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"expr", "5", "+", "5", NULL}; // Argumente für expr
    char *env[] = {NULL}; // Keine zusätzlichen Umgebungsvariablen

    // Ausführen von expr
    execve("/usr/bin/expr", args, env);

    // Wenn execve fehlschlägt, wird dieser Code ausgeführt
    perror("execve failed");
    return EXIT_FAILURE;
}
