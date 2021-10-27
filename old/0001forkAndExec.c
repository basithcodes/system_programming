#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t getpid();
int main() {
	int id , x , stat;
	int p;
	id=fork();

	if(id==0) {
		printf("you are in child %d\n",getpid());
		char *args[] = {"./Demo","Hello", "C", "Programming", NULL};
		printf("In child stat = %d\n", stat);
		/* sleep(5000); */
		/* execvp("Demo", args); */
		exit(9);
	}

	x=wait(&stat);
	if(id==x) {
		printf("got from child %d\n", x);
		printf("In parent stat = %d\n", stat);
		printf("you are in parent %d\n",getpid());
	}

	return 0;
}
