#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/*
Code loads up a library that the user specifies and invokes that function.

Output:
LD_LIBRARY_PATH=. ./test.out libplusone.so 450
Library: I add 1 to ints
450 -> 451

LD_LIBRARY_PATH=. ./test.out libplustwo.so 450
Library: I add 2 to ints
450 -> 452

LD_LIBRARY_PATH=. ./test.out libplus3.so 450
ERROR: could not read functions from library
*/

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("usage: %s <library> <number>\n", argv[0]);
    exit(1);
  }

  // Grab the library name and number from the user
  char* librarypath = argv[1];
  int thenumber = atoi(argv[2]);

  /*
  Load the library from the path. Use lazy loading to only load the functions
  when we use them
  */
  void* libhandle = dlopen(librarypath, RTLD_LAZY);

  if (libhandle == NULL) {
    fprintf(stderr, "dlopen Error: %s\n", dlerror());
    exit(1);
  }

  /*
  Declare a function pointer and assign it the "do_operation" function from the
  library
  */
  int (*opfunc)(int);
  opfunc = dlsym(libhandle, "do_operation");

  if (opfunc == NULL) {
    printf("ERROR: could not read do_operation function from library.\n");
    exit(1);
  }

  /*
  Declare a function pointer and assign it the "get_library_name" function from
  the library
  */
  char* (*libnamefunc)();
  libnamefunc = dlsym(libhandle, "get_library_name");

  if (libnamefunc == NULL) {
    printf("ERROR: could not read get_library_name function from library.\n");
    exit(1);
  }

  // Segmentation fault is happening somewhere

  printf("Library: %s\n", libnamefunc());
  printf("%d --> %d\n", thenumber, opfunc(thenumber));

  // Close the library functions
  dlclose(libhandle);
}