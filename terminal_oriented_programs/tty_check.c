#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
  struct termios t;
  if (tcgetattr(STDIN_FILENO, &t) == -1) {
    perror("tcgetattr");
  } else {
    printf("tcgetattr() succeeded!\n");
  }
  return 0;
}