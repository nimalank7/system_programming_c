#include <stdio.h>

#include "checksum.h"
#include "encrypt.h"

/*
 * To compile the code run make test_code
 * To run the code run LD_LIBRARY_PATH=. ./test_code works
 * make test_code
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