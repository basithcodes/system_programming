#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* function1();
void* function2();

pthread_mutex_t first_mutex; // mutex lock
pthread_mutex_t second_mutex; // mutex lock

int main(void) {

	pthread_mutex_init(&first_mutex, NULL); // initialize the lock
	pthread_mutex_init(&second_mutex, NULL);

	pthread_t one, two;
	pthread_create(&one, NULL, function1, NULL);
	pthread_create(&two, NULL, function2, NULL);

	pthread_join(one, NULL);
	pthread_join(two, NULL);

	printf("Threads are joined with main thread\n");

	return 0;
}

void* function1() {
	pthread_mutex_lock(&first_mutex);
	printf("Thread one acquired first mutex\n");
	sleep(1);
	pthread_mutex_lock(&second_mutex);
	printf("Thread one acquired second mutex\n");
	pthread_mutex_unlock(&second_mutex);
	printf("Thread one released second mutex\n");
	pthread_mutex_unlock(&first_mutex);
	printf("Thread one released first mutex\n");
	return NULL;
}

void* function2() {
	pthread_mutex_lock(&second_mutex);
	printf("Thread two acquired second mutex\n");
	sleep(1);
	pthread_mutex_lock(&first_mutex);
	printf("Thread two acquired first mutex\n");
	pthread_mutex_unlock(&second_mutex);
	printf("Thread two released second mutex\n");
	pthread_mutex_unlock(&first_mutex);
	printf("Thread two released first mutex\n");
	return NULL;
}
