#include <errno.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define RBUFF 50
#define WBUFF 50

int main(int argc, char *argv[]) {
	char readBuffer[RBUFF], writeBuffer[WBUFF];
	int fd1_w, fd2_r, fd3; 
	int ret;
	char choice;
	fd1_w = fd2_r = fd3 = -1;

	printf("Warning Warning Warning!!!\n\n");
	printf("Beware please dont use any important files.\n\n");
	printf("If you do any write operation then you will delete the whole contents of the file. \n\nProceed? Y/N: ");
	scanf("%c", &choice);
	__fpurge(stdin);
	if (choice == 'Y') {
		printf("\nIf you want to exit the program press CTRL+C\n\n");

	} else {
		printf("Program exited\n");
		exit(4);
	}

	// 1.Open the file truncate the content and put it in write mode
	fd1_w = open(argv[1], O_WRONLY | O_TRUNC);
	if (fd1_w < 0) {
		printf("Failed to open the file.\n");
		exit(1);
	}
	// 2. To read the content from file open the same file in readmode
	fd2_r = open(argv[1], O_RDONLY);
	if (fd2_r < 0) {
		printf("Failed to open the file.\n");
		exit(2);
	}

	// 3. Write some content into write buffer and update that in file
	printf("\nWrite some content into write buffer(limit = %d): ", WBUFF);
	fgets(writeBuffer, WBUFF, stdin);

	ret = write(fd1_w, writeBuffer, strlen(writeBuffer));

	if (ret < 0) {
		printf("Unable to write contents from write buffer to file, fd = %d\n", fd1_w);
		printf("errno = %d", errno);
		exit(3);
	}

	printf("Write Buffer: %s\n\n", writeBuffer);

	// 4. Read the content from the file which was written into the file
	ret = read(fd2_r, readBuffer, ret);

	if (ret < 0) {
		printf("Unable to write contents from write buffer to file, fd = %d\n", fd1_w);
		exit(3);
	}

	printf("Read Buffer: %s\n", readBuffer);

	close(fd1_w);
	close(fd2_r);

	return 0;
}
