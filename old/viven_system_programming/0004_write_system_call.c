#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char userBuffer[512] = "abdul basith\nhi\t \0 hihihi";

	int fd = -1;
	int ret;

	fd = open("newFile.txt", O_WRONLY | O_CREAT, 0664);

	if (fd == -1) {
		printf("Failed to open/create file\n");
		exit(1);
	}

	ret = write(fd, userBuffer, strlen(userBuffer));

	if (ret == -1) {
		printf("Failed to write to the file\n");
		exit(2);
	}
	close(fd);
	return 0;
}
