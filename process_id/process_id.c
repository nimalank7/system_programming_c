#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int id = fork();
	printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
	
	return 0;
}