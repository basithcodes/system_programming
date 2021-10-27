/* Sunil Sir program and my program are similar */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
	char userBuffer[10];
	/* void *userBuffer; */
	int fd, response;
	int i;

	/* Open the file if it exists or create it if it doesnt 
	 * write system call is not covered, so open file in editor 
	 * and some content to it*/
	fd = open("test.txt", O_RDONLY);

	if (fd < 0) {
		printf("Unable to create file.\n");
		exit(1);
	}

	printf("fd = %d\n", fd); 

	response = read(fd,(void *)userBuffer, 4);

	/* response from read */
	if (response == 0) {

		printf("Reached the EOF\n");

	} else if (response > 0) {

		printf("Number of bytes read = %d\n", response);
		/* userBuffer[response] = '\0'; // If not used then it will  */
		                             //show all the content of buffer 
																 //which are garbage values
	/* ((char*)userBuffer)+response = '\0'; */
		printf("%s\n",(char*)userBuffer);

	} else if (response < 0) {
		printf("Failed to read from file(check the permissions of file)\n");
		close(fd);
		exit(2);
	}

	close(fd);

	return 0;
}
