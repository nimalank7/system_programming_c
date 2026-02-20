#include <stdio.h>

int main(int argc, char *argv[]) {
  const char filename[] = "sample.txt";

  // FILE struct needed for using standard I/O
  FILE *fh = fopen(filename, "r");

  if (fh == NULL) {
    printf("Unable to read form file%s\n", filename);
    return (1);
  }

  printf("File '%s' opened\n", filename);

  // Close the file
  fclose(fh);

  return 0;
}