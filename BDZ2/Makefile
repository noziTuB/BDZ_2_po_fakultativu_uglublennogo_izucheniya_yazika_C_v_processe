CC=gcc
CFLAGS=-Iinclude -Wall -g
LIB=build/librbmap.so

all: $(LIB)

$(LIB): src/rbmap.c
	$(CC) $(CFLAGS) -fPIC -shared -o $(LIB) src/rbmap.c

test: $(LIB)
	$(CC) -o build/test tests/test_rbmap.c tests/unity.c -Iinclude -Lbuild -lrbmap
	LD_LIBRARY_PATH=build ./build/test

clean:
	rm -rf build/*
