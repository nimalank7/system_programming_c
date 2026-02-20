GCC=gcc
GCFLAGS=-Wall -g

BINS=random.out shim.so

all: $(BINS)

%.so: %.c
	$(GCC) $(GCFLAGS) -shared -fPIC -o $@ $^ -ldl

%.out: %.c
	$(GCC) $(GCFLAGS) -o $@ $^

clean:
	rm -f $(BINS)