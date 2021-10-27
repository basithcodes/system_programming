#include <stdio.h>
#include <pthread.h>

int display(int y);

int main() {
	int res, ret;
	pthread_t t1;
	ret = pthread_create(&t1, NULL, display, 10);
	if (ret == 0) {
		printf("thread was successfully created\n");
	}
	/* return 0; */
	pthread_join(t1, &res);
	printf("Result from main thread: %d", res);
	return 0;
}

int display(int y) {
	int x = y+15;
	printf("x from display %d", x);
	pthread_exit(x);
}
