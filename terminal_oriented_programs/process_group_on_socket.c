#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
  int sv[2];
  struct termios t;

  // Create a pair of connected sockets (like a bidirectional pipe)
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
    perror("socketpair");
    exit(EXIT_FAILURE);
  }

  printf("Socketpair created: sv[0]=%d, sv[1]=%d\n", sv[0], sv[1]);

  // Try to use terminal I/O control on one end
  if (tcgetattr(sv[0], &t) == -1) {
    perror("tcgetattr");
  } else {
    printf("tcgetattr() unexpectedly succeeded!\n");
  }

  // Try to set foreground process group (another TTY-specific operation)
  if (tcsetpgrp(sv[0], getpgrp()) == -1) {
    perror("tcsetpgrp");
  } else {
    printf("tcsetpgrp() unexpectedly succeeded!\n");
  }

  close(sv[0]);
  close(sv[1]);
  return 0;
}