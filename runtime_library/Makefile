GCC=clang
CFLAGS=-Wall -g
BINS=libplusone.so libplustwo.so test.out

all: $(BINS)

%.so: %.c
	$(GCC) $(CFLAGS) -fPIC -shared -o $@ $^

%.out: %.c
	$(GCC) $(CFLAGS) -o $@ $^

clean:
	rm $(BINS)