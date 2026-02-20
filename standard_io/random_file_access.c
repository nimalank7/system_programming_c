#include <stdio.h>

int main(int argc, char *argv[]) {
  // size_t value = 4;
  FILE *fPointer = fopen("random_file_access.txt", "w+");

  // Write "I ate 3 pumpkins today" into the file
  fputs("I ate 3 pumpkins today\n", fPointer);

  // Position 7 is the " " after "3"
  fseek(fPointer, 7, SEEK_SET);
  fputs(" bacon slices on Friday\n", fPointer);

  fclose(fPointer);
  return 0;
}