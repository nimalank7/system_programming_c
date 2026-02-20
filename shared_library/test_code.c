#include <stdio.h>

#include "checksum.h"
#include "encrypt.h"

/*
Use LD_LIBRARY_PATH=. ./test_code_dynamic.out to run the binary against the dynamic
library

Use ./test_code_static.out to run the statically linked binary

Use ldd ./test_code_dynamic.out to see the shared libraries
*/

int main() {
  char s[] = "Speak friend and enter";
  encrypt(s);
  printf("Encrypted to '%s'\n", s);
  printf("Checksum is %i\n", checksum(s));
  encrypt(s);
  printf("Decrypted back to '%s'\n", s);
  printf("Checksum is %i\n", checksum(s));
  return 0;
}