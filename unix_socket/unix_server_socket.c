#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define BACKLOG 5
#define BUF_SIZE 100

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  int sfd, cfd;
  int numRead;
  char buf[BUF_SIZE];

  // Create a new server socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
  if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket");
  }
  printf("Server socket fd = %d\n", sfd);

  // Zero out the address, and set family and path.
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, "foo.socket", sizeof(addr.sun_path) - 1);

  // Bind the socket to the address. Note that we're binding the server socket
  // to a well-known address so that clients know where to connect.
  if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) < 0) {
    perror("bind");
  }

  if (listen(sfd, BACKLOG) < 0) {
    perror("listen");
  }

  for ( ; ; ) {
    printf("Waiting to accept a connection...\n");
    // NOTE: blocks until a connection request arrives.
    cfd = accept(sfd, NULL, NULL);
    printf("Accepted socket fd = %d\n", cfd);

    memset(buf, 0, BUF_SIZE);

    // Transfer data from connected socket to stdout until EOF */
    // Read at most BUF_SIZE bytes from the socket into buf.

    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0) {
      // Then, write those bytes from buf into STDOUT.
      if (write(STDOUT_FILENO, buf, numRead) != numRead) {
        perror("partial/failed write");
      }
    }

    if (numRead == -1) {
      perror("read");
    }

    if (close(cfd) < 0) {
      perror("close");
    }
  }
}