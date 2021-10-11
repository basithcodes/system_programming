#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int x;
	int y;

	y = fork();

	if (argc < 1) {
		printf("Please input the arguments first argument program, second argument flag");
		exit(1);
	}

	if (y==0) {
		printf("%d\n", getpid());
		x = execlp("./demo","hello","4",NULL);
		/* printf("%s\n", strerror(errno)); */
		/* if (x == -1) */
		/*   printf("%d\n", x); */
	}
	printf("Executed Successfully\n");

}
