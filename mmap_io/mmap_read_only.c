#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
  char *p1 = malloc(sizeof(char) * 50);
  printf("p1: %p\n", p1);

  int pagesize = sysconf(_SC_PAGE_SIZE);
  if (pagesize == -1) {
    prerror("sysconf");
  }

  // Allocate 2 blocks so 8K
  int buffersize = 2 * pagesize;

  char *p2, *p3;

  // Allocate 2 pages and are aligned to our 4K page size - pointer will start
  // at the beginning of a page
  if (posix_memalign((void **)&p2, pagesize, buffersize)) {
    perror("posix_memalign");
  }

  // 2 pages of R/W memory
  p3 = mmap(NULL, buffersize, PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

  if (p3 == MAP_FAILED) {
    perror("mmap");
  }

  printf("p2: %p\n", p2);
  printf("p3: %p\n", p3);

  printf("writing...\n");
  memset(p2, 5, buffersize);
  memset(p3, 5, buffersize);
  printf("writing done!\n");

  // Make the 2nd page read-only of p2 read only
  if (mprotect(p2 + pagesize, pagesize, PROT_READ) == -1) {
    perror("mprotect");
  }

  // Successfully write to the first page but attempt to write to the second and
  // fail
  for (int i = 0; i < buffersize; i++) {
    printf("%d (%p): writing... \n", i, p2 + 1);
    p2[i] = 3;
  }
  return EXIT_SUCCESS;
}