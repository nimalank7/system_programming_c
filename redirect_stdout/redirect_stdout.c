#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	
	int pid = fork();
	if (pid == -1) {
		return 1;
	}
	
	if (pid == 0) {
		// Child process
		
		int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777); // Create the file if it doesn't exist
		if (file == -1) {
			printf("Could not find program to execute!\n");
			return 2;
		}
		
		printf("The fd to pingResults: %d\n", file); // Goes to STDOUT
		int file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n", file2); // Goes to the file
		close(file);
		
		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		if (err == -1) {
			printf("Could not find program to execute!\n");
			return 2;
		}
	} else {
		int wstatus;
		// Parent Process
		wait(&wstatus);
		if (WIFEXITED(wstatus)) { // Normal termination
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0) {
				printf("Success!\n");
			} else {
				printf("Failure with status code %d\n", statusCode);
			}
		}
		printf("Success!\n");
	}
	
	return 0;
}