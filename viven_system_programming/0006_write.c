#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	key_t key = ftok("shmfile", 65);
	size_t size = 1024;

	int shmid = shmget(key, size, IPC_CREAT|0666);
	char *str = (char *)shmat(shmid, NULL, 0);
	fgets(str, size, stdin);
	printf("Write to shared memory: %s\n", str);
	return 0;
}
