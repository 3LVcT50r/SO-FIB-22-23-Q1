#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg, int exit_status)
{
perror(msg);
exit(exit_status);
}

int main (int argc, char *argv[]) {
    char buffer[80];
    int pid, i;
    if (argc > 1) {
        pid = fork();

        switch(pid) {
            case 0:
            sprintf(buffer, "HIJO: %d\n", getpid());
            write(1, buffer, strlen(buffer));
            sprintf(buffer, "Parámetros: %s\n", argv[1]);
            write(1, buffer, strlen(buffer));
            break;
            
            case -1:
            error_y_exit("FALLO EN EL FORK", 1);
            break;

            default:
            sprintf(buffer, "PADRE: %d\n", getpid());  
            write(1, buffer, strlen(buffer));    
        }
        while(1);
    }
    
    return 0;
}