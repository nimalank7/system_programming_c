#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int fd;
  char buf[14];

  // Write

  fd = open("myfile.txt", O_CREAT | O_WRONLY, 0600);

  if (fd == -1) {
    printf("Failed to create and open the file.\n");
    exit(1);
  }

  write(fd, "Hello World!\n", 13);

  close(fd);

  // Read

  fd = open("myfile.txt", O_RDONLY);

  if (fd == -1) {
    printf("Failed to open and read the file.\n");
    exit(1);
  }

  read(fd, buf, 13);
  buf[13] = '\0';

  close(fd);

  printf("buff: %s\n", buf);

  return 0;
}