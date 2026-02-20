#include <stdio.h>

int main(int argc, char *argv[]) {
  // Needs a NULL check
  FILE *fPointer = fopen("sample.txt", "r");

  char singleLine[150];

  while (!feof(fPointer)) {
    /*
    fgets takes:
        (i) array to hold the characters
        (ii) block size
        (iii) FILE pointer
    Reads the line and appends it to the array
    */
    fgets(singleLine, 150, fPointer);

    // Outputs to screen and adds a \n so we see 'Line 1\n\n'
    puts(singleLine);
  }

  fclose(fPointer);

  return 0;
}