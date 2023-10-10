#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int x;
    read(0, &x, sizeof(int));
    char buff[4];
    sprintf(buff, "%d\n", x);
    write(1, buff, strlen(buff));
}