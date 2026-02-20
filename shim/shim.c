#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int rand() {
  /*
  Just adding this will return 42 for the random numbers

  return 42;
  */

  int (*original_rand)(void) = dlsym(RTLD_NEXT, "rand");
  // Modify our random function to get numbers under 100
  return original_rand() % 100;
}