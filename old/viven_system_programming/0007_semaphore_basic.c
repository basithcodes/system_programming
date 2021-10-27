#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

// Using inbuilt struct, not defining my own. Its creating a conflict
struct sembuf operations;

int main(void) {
	int id;
	key_t key = 1234;
	int retval;

	/* Get the index for the semaphore with external name key */
	id = semget(key, 1, 0666|IPC_CREAT);

	if (id < 0) {
		printf("Program sema cannot find semaphore, exiting.\n");
		exit(1);
	}

	/* Do a semaphore p operation */
	printf("Program sema about to do a p operation.\n");

	/* setup the sembuf structure */
	/* which semaphore in the semphore aray */
	operations.sem_num = 0;

	/* Set the flag so we will wait */
	operations.sem_flg = SEM_UNDO;

	/* So do the operation */
	retval = semop(id, &operations, 1);
	if(retval == 0) {
		printf("Successful p operations by program sema.\n");
	}

	else {
	printf("Sema: P operation did not succeed\n");
	perror("REASON");
	}

	printf("Accessing shared resource\n");
	sleep(2);

	printf("Program sema about to do a v operation\n");

	/* set up the sem buf structure */
	/* which semphore in the semaphore array */
	operations.sem_num = 0;
	/* which operation? add 1 to semaphore val */
	operations.sem_op = 1;
	/* set the flag so we will wait */
	operations.sem_flg = SEM_UNDO;

	/* so do the operations */
	retval = semop(id, &operations, 1);
	if(retval == 0) {
		printf("Successful v operation by program sema\n");
	}

	else {
		printf("Sema: v operation did not succeed\n");
		perror("REASON");
	}


}

