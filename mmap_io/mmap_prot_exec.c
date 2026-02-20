#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

// Define machine code for a small function that returns 42
// This is platform-specific (x86-64 in this case)
unsigned char code[] = {
    0xb8, 0x2a, 0x00, 0x00, 0x00,  // mov eax, 42
    0xc3                           // ret
};

int main() {
  size_t code_size = sizeof(code);
  size_t page_size = sysconf(_SC_PAGESIZE);  // Get system page size
  void* exec_mem;

  // Step 1: Allocate memory with PROT_READ | PROT_WRITE so we can copy into it
  exec_mem = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (exec_mem == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  // Copy the machine code into the writable memory
  memcpy(exec_mem, code, code_size);

  // Step 2: Change the protection to PROT_READ | PROT_EXEC to make it
  // executable
  if (mprotect(exec_mem, page_size, PROT_READ | PROT_EXEC) == -1) {
    perror("mprotect");
    munmap(exec_mem, page_size);
    return 1;
  }

  // Define a function pointer with the same signature as the code
  int (*func)() = (int (*)())exec_mem;

  // Call the function in executable memory and print the result
  int result = func();
  printf("Result from executable memory: %d\n", result);  // Expected output: 42

  // Unmap the memory when done
  if (munmap(exec_mem, page_size) == -1) {
    perror("munmap");
    return 1;
  }

  return 0;
}