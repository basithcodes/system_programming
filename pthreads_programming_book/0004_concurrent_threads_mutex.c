#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *thread_fun1(void *);
void *thread_fun2(void *);
void do_wrap_up(int, int);

pthread_mutex_t r3_mtx = PTHREAD_MUTEX_INITIALIZER;

int r1, r2, r3;

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Please put one command line argument\n");
		exit(1);
	}

  pthread_t thread1, thread2;
  int res;

	r3 = atoi(argv[1]);

  res = pthread_create(&thread1, NULL, thread_fun1, &r1);
  if (res != 0) {
    printf("Thread 1 Creation Failed\n");
    printf("error: %s\n", strerror(errno));
  }

  res = pthread_create(&thread2, NULL, thread_fun2, &r2);
  if (res != 0) {
    printf("Thread 2 Creation Failed\n");
    printf("error: %s\n", strerror(errno));
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  do_wrap_up(r1, r2);
  return 0;
}

void *thread_fun1(void *arg) {
  int i, j, x;

	pthread_mutex_lock(&r3_mtx);
	if (r3 > 0) {
		x = r3;
		r3--;
	} else {
		x = 1;
	}
	pthread_mutex_unlock(&r3_mtx);

  for (i = 0; i < 4; i++) {
    printf("do_one_thing\n");
    for (j = 0; j < 10000; j++) {
      x = x + i;
    }
    (*(int *)arg)++;
  }
  pthread_exit(0);
}

void *thread_fun2(void *arg) {
  int i, j, x;

	pthread_mutex_lock(&r3_mtx);
	if (r3 > 0) {
		x = r3;
		r3--;
	} else {
		x = 1;
	}
	pthread_mutex_unlock(&r3_mtx);

  for (i = 0; i < 4; i++) {
    printf("do_another_thing\n");
    for (j = 0; j < 10000; j++) {
      x = x + i;
    }
    (*(int *)arg)++;
  }
  pthread_exit(0);
}

void do_wrap_up(int num1, int num2) {
  int total = 0;
  total = num1 + num2;
  printf("\n\nWrap up\n");
  printf("do_one_thing: %d\ndo_another_thing: %d\ntotal: %d\n", r1, r2, total);
}
