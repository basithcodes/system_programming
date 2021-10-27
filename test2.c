#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


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
	int ret;
	ret = fork();
	printf("Im in new thread: %ld\n", pthread_self());
	if (ret == 0) {
		execvp("/home/basith/Coding/system_programming/test1", NULL);
		printf("We are in child process\n");
		printf("Child PID = %d\n", getpid());
		printf("Child TID = %d\n", gettid());

	} else {
		printf("We are in parent process\n");
		printf("Parent PID = %d\n", getpid());
		printf("Parent TID = %d\n", gettid());
	}

	pthread_exit(0);
}
