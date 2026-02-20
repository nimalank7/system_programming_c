#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv) {
	// open the file
	int fd;
	fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
	    fprintf(stderr, "errno = %i\n", perror("Custom error message!"));
	    exit(-1);
    }   
	
	// reads its contents and print them to stdout
	char c;
	while (read(fd, &c, 1) > 0) {
		fputc(c, stdout);
	}
	
	// close the file
	close(fd);
}