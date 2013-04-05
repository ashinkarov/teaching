

CFLAGS = -Wall -std=c99 -O3 -D_BSD_SOURCE

main: main.o tree.o mystring.o
	$(CC) -o main  $^

mystring.o: mystring.h
tree.o: mystring.h tree.h
main.o: tree.h

clean:
	$(RM) *.o main
