#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mtx;

int glob;

void* thread_fun_1(void* args);
void* thread_fun_2(void* args);

int main(void) {
	pthread_t t1, t2;
	void* ret1, *ret2;
	int loops = 2000;

	pthread_create(&t1, NULL, thread_fun_1, &loops);
	pthread_create(&t2, NULL, thread_fun_2, &loops);

	pthread_join(t1, &ret1);
	pthread_join(t2, &ret2);

	printf("ret from thread 1 = %d\n", *(int *)&ret1);
	printf("ret from thread 2 = %d\n", *(int *)&ret2);
	printf("\nGlobal = %d\n", glob);

	pthread_exit(0);
}

void* thread_fun_1(void* args) {
	int loc, i;
	int loops = *(int *)args;

	for (i = 0; i < loops; i++) {
		pthread_mutex_lock(&mtx);
		loc = glob;
		loc++;
		glob = loc;
		pthread_mutex_unlock(&mtx);
	}
	return (void *)1;
}

void* thread_fun_2(void* args) {
	int loc, i;
	int loops = *(int *)args;

	for (i = 0; i < loops; i++) {
		pthread_mutex_timedlock(&mtx, 1);
		loc = glob;
		loc++;
		glob = loc;
		pthread_mutex_unlock(&mtx);
	}
	return (void *)2;
}
