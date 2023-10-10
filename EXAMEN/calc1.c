#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void Usage() {
	char buf[80];
	sprintf(buf, "Parametros incorrectos: \n");
	write(1, buf, strlen(buf));
	exit(1);
}

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {
	char buf[80];

	if (argc != 3) Usage();
	int cont=0, n=atoi(argv[1]);
	int pids[n];
	
	for(int i=0; i < n; ++i) {

		int pid;
		pid=fork();

		if(pid==0) {
			execlp("./hijo1", "hijo1", argv[2], NULL);
			error_y_exit("Error execlp");
		}
		else if(pid < 0) error_y_exit("Error fork");

		int status, ret;

		if ( (ret = waitpid(-1, &status, WNOHANG)) > 0) {
			int code;
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
				sprintf(buf, "%d ended correctly\n", ret);
				write(1, buf, strlen(buf));
				for(int i=0; i < n; ++i)
					if (pids[i] != ret) kill(pids[i], SIGKILL);
			}
			else if (WIFEXITED(status) && (code = WEXITSTATUS(status)) != 0) {
				sprintf(buf, "%d causa de error %d\n", ret, code);
				write(1, buf, strlen(buf));
				++cont;
			}
			else if (!WIFEXITED(status)) error_y_exit("Error en el hijo");
		}
	}

	int status, ret;
	while ( (ret = waitpid(-1, &status, 0)) > 0) {
		int code;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			sprintf(buf, "%d ended correctly\n", ret);
			write(1, buf, strlen(buf));
			for(int i=0; i < n; ++i)
				if (pids[i] != ret) kill(pids[i], SIGKILL);
		}
		else if (WIFEXITED(status) && (code = WEXITSTATUS(status)) != 0) {
			sprintf(buf, "%d causa de error %d\n", ret, code);
			write(1, buf, strlen(buf));
			++cont;
		}
		else if (!WIFEXITED(status)) error_y_exit("Error en el hijo");
	}

	if (cont == n) {
		sprintf(buf, "Incalculable\n");
		write(1, buf, strlen(buf));
	}
}