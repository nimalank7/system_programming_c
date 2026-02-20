#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
  ssize_t example = 4;

  int fd = open("file.hole", O_CREAT | O_WRONLY, 0644);

  if (fd < 0) {
    perror("create error");
  }

  if (write(fd, buf1, 10) != 10) {
    perror("buf1 write error");
  }

  /* offset now = 10 */
  if (lseek(fd, 16384, SEEK_SET) == -1) {
    perror("lseek error");
  }

  /* offset now = 16384 */
  if (write(fd, buf2, 10) != 10) {
    perror("buf2 write error");
  }

  /* offset now = 16394 */
  exit(0);
}
