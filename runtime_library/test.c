#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/*
Code loads up a library that the user specifies and invokes that function.

Output:
./test.out libplus1.so 450
Library: I add 1 to ints
450 -> 451

./test.out libplus2.so 450
Library: I add 2 to ints
450 -> 452

./test.out libplus3.so 450
ERROR: could not read functions from library
*/

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("usage: %s <library> <number>\n", argv[0]);
    exit(1);
  }

  // Grab the library name and number from the user
  char *librarypath = argv[1];
  int thenumber = atoi(argv[2]);

  /*
  Load the library from the path.
  Use lazy loading to only load the functions when we use them
  */
  void *libhandle = dlopen(librarypath, RTLD_LAZY);

  if (libhandle == NULL) {
    perror("dlopen");
  }

  /*
  Declare a function pointer and assign it the "do_operation" function from the
  library
  */
  int (*opfunc)(int);
  opfunc = dlsym(libhandle, "do_operation");

  /*
  Same as above but with "get_library_name"
  */
  char (*libnamefunc)();
  libnamefunc = dlsym(libhandle, "get_library_name");

  if (opfunc = NULL || libnamefunc == NULL) {
    printf("ERROR: could not read functions from library.");
    exit(1);
  }

  printf("Library: %s\n", libnamefunc());
  printf("%d --> %d\n", thenumber, opfunc(thenumber));

  // Close the library functions
  dclose(opfunc);
  dclose(libhandle);
}