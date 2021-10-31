#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *printEmployeeDetails(void * args);

struct employee {
	char *name;
	int salary;
	unsigned short int age;
} *emp;

void empInit(void) {
	emp = (struct employee *)malloc(sizeof(struct employee));
	emp->name = "Abdul Basith";
	emp->salary = 80000;
	emp->age = 29;
}

int main(void) {
	int count = 0;
	pthread_t ti;

	empInit();

	char* ret;

	printf("hello from main thread\n");

	pthread_create(&ti, NULL, printEmployeeDetails, NULL);

	pthread_join(ti, (void *)&ret);

	while(count != 5) {
		printf("Return value of new thread(employeeDetails): %s\n", ret);
		count++;
		sleep(1);
		if(count == 5) {
			break;
		}
	}
	while(1);

	return 0;
}

void *printEmployeeDetails(void* arg) {
	printf("hello from employee details thread\n");
	printf("Name: %s\n", emp->name);
	printf("salary: %d\n", emp->salary);
	printf("age: %u\n", emp->age);
	return "hello";
}
