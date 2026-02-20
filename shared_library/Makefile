GCC=gcc
CFLAGS=-Wall -g

encrypt.o: encrypt.c
	$(GCC) $(CFLAGS) -c encrypt.c -o encrypt.o

checksum.o: checksum.c
	$(GCC) $(CFLAGS) -c checksum.c -o checksum.o

# Static library
libsecurity.a: encrypt.o checksum.o
	ar -rcs libsecurity.a encrypt.o checksum.o

# Dynamic library
libsecurity.so: encrypt.o checksum.o
	$(GCC) $(CFLAGS) -fPIC -shared checksum.o encrypt.o -o libsecurity.so

# Link against static library and generate test_code_static.out 
test_code_static: test_code.c libsecurity.a
	$(GCC) $(CFLAGS) test_code.c -I . -L . -lsecurity -o test_code_static.out

# Link against dynamic library and generate test_code_dynamic.out
test_code_dynamic: test_code.c libsecurity.so
	$(GCC) $(CFLAGS) test_code.c -I. -L. -lsecurity -o test_code_dynamic.out

clean:
	rm *.o *.a *.so