CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

all: matmul transpose

matmul: common.o matmul.o
transpose: common.o transpose.o

matmul.o: common.h
transpose.o: common.h
common.o: common.h

clean:
	$(RM) *.o matmul transpose
