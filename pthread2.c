#include <stdio.h>
#include <pthread.h>

int thread_fun1(int x);
int thread_fun2(int y);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int glob;

int main() {
	int loop = 2000;
	int res1, res2;
	pthread_t t1,t2;
	
	pthread_create(&t1, NULL, thread_fun1, loop);
	pthread_create(&t2, NULL, thread_fun2, loop);
	pthread_join(t1,&res1);
	pthread_join(t2,&res2);
	printf("res1 = %d\nres2 = %d\n", res1, res2);
	printf("glob = %d\n", glob);
	return 0;
}

int thread_fun1(int x) {
	int loc, i, loop, s;
	loop = x;
	for (i = 0; i < loop; i++) {
		// we need to lock the shared resources when its being use
		// if some other thread access it then it wont be able to access it
		s = pthread_mutex_lock(&mutex);
		loc = glob;
		loc++;
		glob = loc;
		// after the operation is completed then unlock it so that other thread 
		// can use the shared resources(in this case global variable)
		s = pthread_mutex_unlock(&mutex);
	}
}

int thread_fun2(int y) {
	int loc, i, loop, s;
	loop = y;
	for (i = 0; i < loop; i++) {
		// we need to lock the shared resources when its being use
		// if some other thread access it then it wont be able to access it
		s = pthread_mutex_lock(&mutex);
		loc = glob;
		loc++;
		glob = loc;
		// after the operation is completed then unlock it so that other thread 
		// can use the shared resources(in this case global variable)
		s = pthread_mutex_unlock(&mutex);
	}
}
