#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 8

int esNumero(char *str) {
	if (str == NULL) return 0;
	else if (*str == '-') ++str;

	for (int i = 0; str[i] != '\0'; ++i) {
		if (!(str[i] >= '0' && str[i] <= '9') || i >= MAX_SIZE)
			return 0;
	}

	return 1;
}

unsigned int pot10(int t) {
	int p = 1;
	for (int i = 0; i < t; ++i) {
		p *= 10;
	}
	return p;
}

unsigned int char2int(char c) {
	return c - '0';
}

int mi_atoi(char *s) {

	int len = strlen(s);

	int num = 0;
	int neg = 1;
	int i = 0;
	if (s[0] == '-') {
		neg = -1;
		i = 1;
	}
	while (i < len-2) {
		num += char2int(s[i]);
		num *= 10;
	}
	num += s[len-1];

	return neg*num;
}

int main(int argc, char *argv[]) {

	char buf[80];
	for (int i = 1; i < argc; ++i) {
		if (!esNumero(argv[i]))
			sprintf(buf, "Error: el parámetro \"%s\" no es un numero\n", argv[i]);
			return 0;
		else
			total += mi_atoi(argv[i]);
	}
	write(1, total, strlen(buf));
	return 0;
}