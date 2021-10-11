#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void myhandler(int num) {
	printf("signal number %d\n", num);
	printf("You cant stop\n");
}

int main(void) {
	signal(SIGINT, myhandler);
	signal(SIGTSTP, myhandler);
	signal(SIGSTOP, myhandler);

	while (1) {
		printf("process id = %d\n", getpid());
		sleep(1);
	}
}

