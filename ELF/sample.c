#include <stdio.h>

/* .data — initialized global variable */
int global_init = 42;

/* .bss — uninitialized global variable */
int global_uninit;

/* .rodata — read-only data (string literal) */
const char* message = "Hello ELF";

/* .data (static storage with initializer) */
static int static_init = 7;

/* .bss (static storage without initializer) */
static int static_uninit;

/* .text — executable machine code */
void hello() { printf("%s\n", message); }

int main() {
  /* stack — local variables */
  int local_var = 10;

  hello();

  printf("global_init=%d\n", global_init);
  printf("global_uninit=%d\n", global_uninit);
  printf("static_init=%d\n", static_init);
  printf("static_uninit=%d\n", static_uninit);
  printf("local_var=%d\n", local_var);

  return 0;
}