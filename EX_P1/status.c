#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char buff[128];

void usage() {
    sprintf(buff, "Mal uso del programa");
    write(1, buff, strlen(buff));
    exit(1);
}

void error_y_exit(int s, char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc < 1) usage();

    for (int i = 1; i < argc; ++i) {
        int pid = fork();
        if (pid < 0) error_y_exit(1, "Error en el fork");
        if (pid == 0) {
            sprintf(buff, "/proc/%s/status", argv[i]);
            execlp("grep", "grep", "State", buff, NULL);
            error_y_exit(1, "Error en el execlp");
        }
    }
}