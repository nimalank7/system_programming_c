#include <stdio.h>
#include <stdlib.h>

/*
LD_PRELOAD=./shim.so ./random.out
*/

int main() {
  for (int i = 0; i < 5; i++) {
    printf("%d: %d\n", i, rand());
  }
}