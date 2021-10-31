#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int, int);

int shared_mem_id;
int* shared_mem_ptr;
int *r1p;
int *r2p;

int main(void) {
	pid_t child1_pid, child2_pid;
	int status;

	/*Initialize Shared Memory Segment*/
	shared_mem_id = shmget(IPC_PRIVATE, sizeof(int), 0660);
	shared_mem_ptr = (int *)shmat(shared_mem_id, (void *)0, 0);
	r1p = shared_mem_ptr;
	r2p = shared_mem_ptr + 1;

	*r1p = 0;
	*r2p = 0;

	if ((child1_pid = fork()) == 0) {
		do_one_thing(r1p);
		exit(0);
	}
	printf("\nParent\n");

	if ((child2_pid = fork()) == 0) {
		do_another_thing(r2p);
		exit(0);
	}

	waitpid(child1_pid, &status, 0);
	waitpid(child2_pid, &status, 0);

	do_wrap_up(*r1p, *r2p);
	return 0;
}

void do_one_thing(int *r1p) {
	int i, j, x = 0;
	for (i = 0; i < 4; i++) {
		printf("Do one thing\n");
		for (j = 0; j < 10000; j++) {
			x = x + i;
		}
		(*r1p)++;
	}
}

void do_another_thing(int *r2p) {
	int i, j, x = 0;
	for (i = 0; i < 4; i++) {
		printf("Do another thing\n");
		for (j = 0; j < 10000; j++) {
			x = x + i;
		}
		(*r2p)++;
	}
}

void do_wrap_up(int r1p, int r2p) {
	int total;
	total = r1p + r2p;
	printf("\n\nWrap Up\n");
	printf("One thing: %d\nOther thing: %d\nTotal: %d\n", r1p, r2p, total);
}

