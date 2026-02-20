GCC=clang
CFLAGS=-Wall -g
BINS=libplus1.so libplus2.so test.out

all: $(BINS)

%.so: %.c
	$(GCC) $(CFLAGS) -fPIC -shared -o $@ $^

%.out: %.c
	$(GCC) $(CFLAGS)-o $@ $^

clean:
	rm $(BINS)