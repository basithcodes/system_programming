#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <linux/sched.h>
#include <sched.h>
#define _GNU_SOURCE
void* thread_fun1(void *);
int glob;

int main(void) {

	pthread_t t1;
	void * res;
	int ret;

	printf("Im in main thread: %ld\n", pthread_self());

	pthread_create(&t1, NULL, thread_fun1, NULL);

	pthread_join(t1, (void *)&res);

	printf("Exiting main thread: %ld\n", pthread_self());

	return 0;
}

void* thread_fun1(void *args) {
	int ret, stat;
	ret = pthread_atfork(NULL, NULL, NULL);
	
	printf("Im in new thread: %ld\n", pthread_self());
	if (ret == 0) {
		printf("We are in child process\n");
		printf("Child PID = %d\n", getpid());
		printf("Child TID = %d\n", gettid());
		exit(0);

	} 
	else {
		printf("We are in parent process\n");
		printf("Parent PID = %d\n", getpid());
		printf("Parent TID = %d\n", gettid());
	}
	ret = wait(&stat);

	printf("ret = %d stat = %d\n", ret, stat);

	pthread_exit(0);
}
