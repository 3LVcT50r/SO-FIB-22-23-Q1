#include <stdio.h>
#include <string.h>
#include <unistd.h>

void Usage(char buf[128]) {
	sprintf(buf, "Usage:listaParametros arg1 [arg2..argn]\nEste programa escribe por su salida la lista de argumentos que recibe \n");
}


int main(int argc,char *argv[]) {

	char buf[128];

	for (int i = 0; i < argc; i++) {
		if (argc == 1) {
			Usage(buf);
		} 
		else {
			if (i == 0){
				sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			} 
			else {
				sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			}
		}
		
		write(1,buf,strlen(buf));
	}

	return 0;
}