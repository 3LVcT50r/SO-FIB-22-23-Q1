#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

	char buffer[128];

	int A;
	int *PA;

	PA = &A;
	*PA = 4;
	 if (*PA == A) {
	 	sprintf(buffer, "ESTE MSG DEBERIA DE SALIR SIEMPRE\n");
	 } else {
	 	sprintf(buffer, "ESTE MSG NO DEBERIA DE SALIR\n");
	 }

	 write( 1, buffer, strlen(buffer) );
}