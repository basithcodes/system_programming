#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int i;
	printf("called by exec pid = %d\n",getpid());
	for(i=0;i<argc;i++) {
		printf("%d\n",i);
	}

	exit(2);
}
