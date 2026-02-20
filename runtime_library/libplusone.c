#include <stdio.h>

// This function runs automatically when the library is loaded
void __attribute__((constructor)) init_library() {
    printf("Running init_library function.\n");
}

// This function runs automatically when the library is unloaded (or program exits)
void __attribute__((destructor)) cleanup_library() {
    printf("Running cleanup_library function.\n");
}

char *get_library_name() { return "Add 1 to number:"; }

int do_operation(int i) { return i + 1; }
