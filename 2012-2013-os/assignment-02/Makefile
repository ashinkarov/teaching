

CFLAGS := -Wall -Wextra -pedantic -std=c99 -D_GNU_SOURCE -D_BSD_SOURCE

all: search fork-thread

fork-thread: fork-thread.c
	$(CC) $(CFLAGS) $^ -o $@ -lrt -pthread

search: search.o
search.o: search.c

clean:
	$(RM) *.o search fork-thread
