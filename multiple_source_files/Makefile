GCC=gcc
CFLAGS=-Wall -g
BINS=encrypt.o checksum.o test_code.out

all: $(BINS)

%.o: %.c
	$(GCC) $(CFLAGS) $< -c $@

%.out: %.c
	$(GCC) $(CFLAGS) encrypt.o checksum.o $< -o $@

clean:
	rm *.o $(BINS)