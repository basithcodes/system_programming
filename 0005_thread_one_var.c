#include <alloca.h>
#include <stdio.h>
#include <pthread.h>
void* thread_fun1(void *);
void* thread_fun2(void *);

void print_stack_pointer(void);
int glob;

int main(void) {

	pthread_t t1;
	void * res;
	int ret;

	printf("Im in main thread: %ld\n", pthread_self());

	print_stack_pointer();

	pthread_create(&t1, NULL, thread_fun1, NULL);

	pthread_join(t1, (void *)&res);

	register void *sp asm ("sp");
	printf("sp = %p\n", sp);

	printf("Exiting main thread: %ld\n", pthread_self());

	return 0;
}

void* thread_fun1(void *args) {
	int ret = 3;
	pthread_t t2;
	/*int *ptr = (int*)alloca(1);*/
	/*printf("ptr = %p\n", ptr);*/
	pthread_create(&t2, NULL, thread_fun2, &ret);
	pthread_join(t2, NULL);
	printf("thread1 %d\n", ret);
	register void *sp asm ("sp");
	printf("thread 1 sp = %p\n", sp);
	print_stack_pointer();
	pthread_exit(0);
}

void* thread_fun2(void *args) {
	int *t = (int *)args;
	printf("thread2 %d\n", *t);
	print_stack_pointer();
	*t = 4;
	register void *sp asm ("sp");
	printf("thread 2 sp = %p\n", sp);
	pthread_exit(0);
}

void print_stack_pointer() {
	void *p = NULL;
	printf("%p\n", (void*)&p);
}
