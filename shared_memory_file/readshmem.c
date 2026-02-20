#include <string.h>
#include <stdio.h>
#include "shared_memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char *argv[]) {
	// Doesn't accept arguments as it is just reading
    if (argc != 1) {
		printf("usage - %s // no args", argv[0]);
		return -1;
	}
	
	// grab the shared memory block
	char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
	if (block == NULL) {
		printf("ERROR: couldn't get block\n");
		return -1;
	}
	
	printf("Reading: \"%s\"\n", block);
	
	detach_memory_block(block);
	
	return 0;

}
