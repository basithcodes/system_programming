#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

int glob = 0, lock = 1;

void* thread_fun1(void *);
void* thread_fun2(void *);

int main(void) {

	int loop = 20000;
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

	while (1) {
		if (lock) {
			for (i = 0; i < loop_1; i++) {
				lock = 0;
				loc = glob;
				loc++;
				glob = loc;
			}
			lock = 1;
		}
		if (lock == 1)
			break;
	}
}

void* thread_fun2(void *args) {
	int loop_2 = *(int *)args;
	int i,loc;

	while (1) {
		if (lock) {
			for (i = 0; i < loop_2; i++) {
				lock = 0;
				loc = glob;
				loc++;
				glob = loc;
			}
			lock = 1;
		}
		if (lock == 1)
			break;
	}
}
