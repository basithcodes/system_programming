#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *thread_fun1(void *);
void *thread_fun2(void *);
void do_wrap_up(int, int);

int r1, r2;

int main(void) {
  pthread_t thread1, thread2;
  void *ret;
  int res;

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

  pthread_join(thread1, ret);
  /*printf("Thread1 returns: %d\n", *(int *)&ret);*/

  pthread_join(thread2, ret);
  /*printf("Thread2 returns: %d\n", *(int *)&ret);*/

  do_wrap_up(r1, r2);
  return 0;
}

void *thread_fun1(void *arg) {
  int i, j, x = 0;
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
  int i, j, x = 0;
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
