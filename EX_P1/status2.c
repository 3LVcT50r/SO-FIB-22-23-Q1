#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char buff[128];

void usage() {

    sprintf(buff, "Mal uso del programa\n");
    write(1, buff, strlen(buff));
    exit(1);
}

void error_y_exit(int s, char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc < 2) usage();

    for (int i = 1; i < argc; ++i) {
        int pid = fork();
        if (pid < 0) error_y_exit(1, "Error en el fork\n");
        if (pid == 0) {
            sprintf(buff, "/proc/%d/status", atoi(argv[i]));
            execlp("grep", "grep", "State", buff, NULL);
            error_y_exit(1, "Error en el execlp\n");
        }
    }

    int status, ret;
    while (ret = waitpid(-1, &status, 0) > 0) {
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                sprintf(buff, "Proceso %d no encontrado\n", status);
                write(1, buff, strlen(buff));
                exit(1);
            }
        } 
        else error_y_exit(1, "Error en el waitpid\n");
    }
}