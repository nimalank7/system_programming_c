#include <stdio.h>

#include "checksum.h"
#include "encrypt.h"

/*
Use LD_LIBRARY_PATH=. ./test_code_dynamic to run the binary against the dynamic
library
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