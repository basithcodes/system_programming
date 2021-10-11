#include <sys/shm.h>
#include <stdio.h>

int main(void) {
	key_t key = ftok("shmfile", 65);
	size_t size = 1024;

	int shmid = shmget(key, size, IPC_CREAT|0666);
	char *str = (char*)shmat(shmid, NULL, 0);
	printf("Read from shared memory: %s\n", str);
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
