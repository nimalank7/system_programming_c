#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int rand() {
  // Return 42 instead of random numbers
  return 42;
}