#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	char userBuffer[512];
	int ret, i;
	if (argc < 2) {
		printf("Enter the file name\n");
		exit(1);
	}

	int fd = -1;

	fd = open(argv[1], O_RDONLY);

	if (fd < 0) {
		printf("Open system call failed to open the file.\n");
		exit(2);
	}

	// Read data from file and write it to stdout/terminal 
	// screen using printf
	while((ret = read(fd, userBuffer, 512)) != EOF) {
		if (ret == 0) {
			break;
		}

		for (i = 0; i < ret; i++) {
			printf("%c", *(userBuffer+i));
			*(userBuffer+i) = 0;
		}
	}
	
	return 0;
}


