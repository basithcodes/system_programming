#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void) {
	int fd = open("/home/basith/Documents/duaDaily.txt", O_RDONLY);
	if (fd < 0) { 
		printf("Open has failed to open the file: %d\n", fd);
		exit(0);
	}
	printf("fd table entry number: %d\n", fd);
	return 0;
}
