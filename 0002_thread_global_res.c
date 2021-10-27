#include <stdio.h>
#include <pthread.h>

int glob = 0;


void* thread_fun1(void *);
void* thread_fun2(void *);

int main(void) {

	int loop = 2000;
	int res;

	pthread_t t1, t2;

	pthread_create(&t1, NULL, thread_fun1, &loop);

	pthread_create(&t2, NULL, thread_fun2, &loop);

	pthread_join(t1, (void *)&res);

	pthread_join(t2, (void *)&res);

	printf("glob = %d\n", glob);

	return 0;
}

void* thread_fun1(void *args) {
	int loop_1 = *(int *)args;
	int i,loc;

	for (i = 0; i < loop_1; i++) {
		loc = glob;
		loc++;
		glob = loc;
	}
}

void* thread_fun2(void *args) {
	int loop_2 = *(int *)args;
	int i,loc;

	for (i = 0; i < loop_2; i++) {
		loc = glob;
		loc++;
		glob = loc;
	}
}
