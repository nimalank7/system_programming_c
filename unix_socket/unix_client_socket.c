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
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define BUF_SIZE 100
#define SA struct sockaddr

// This doesn't read the server response

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    int numRead;
    int sfd;
    char buf[BUF_SIZE];

    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
    if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
      perror("socket");
      exit(-1);
    }
    
    printf("Client socket fd = %d\n", sfd);


    // Construct server address, and make the connection.
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "foo.socket", sizeof(addr.sun_path) - 1);

    // Connects the active socket referred to be sfd to the listening socket
    // whose address is specified by addr.
    if (connect(sfd, (SA*) &addr, sizeof(addr)) < 0) {
      perror("connect");
      exit(-1);
    }

    // Copy stdin to socket and read at most BUF_SIZE bytes from STDIN into buf
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
      // Then, write those bytes from buf into the socket.
      if (write(sfd, buf, numRead) != numRead) {
        perror("partial/failed write");
        exit(-1);
      }
    }

    if (numRead == -1) {
      perror("read");
      exit(-1);
    }

    // Closes our socket; server sees EOF.
    exit(EXIT_SUCCESS);
}