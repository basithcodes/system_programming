#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
	int x, y, z, stat, cpid;
	x = fork();
	y = fork();

	if(x > 0) {
		printf("\nFORK 1\n");
		printf("You are in parent: PID = %d\n", getpid());
		z = wait(&stat);
		printf("stat = %d z = %d\n", stat, z);
	}

	if(x == 0) {
		printf("\nFORK 1\n");
		printf("You are in child 1 PID = %d\n", getpid());
		exit(0);
	}

	if(x > 0 && y > 0) {
		printf("\nFORK 2\n");
		printf("You are in parent PID = %d\n", getpid());
		z = wait(&stat);
		printf("stat = %d z = %d\n", stat, z);
	} 

	if(x > 0 && y == 0) {
		printf("\nFORK 2\n");
		printf("You are in sibling PID = %d\n", getpid());
		exit(0);
	} 

	if(x == 0 && y > 0) {
		printf("\nFORK 2\n");
		printf("You are in child c1 PID = %d\n", getpid());
		z = wait(&stat);
		printf("stat = %d z = %d\n", stat, z);
	} 

	if(x == 0 && y == 0) {
		printf("\nFORK 2\n");
		printf("You are in grand child c3 PID = %d\n", getpid());
		exit(0);
	} 

	return 0;
}
