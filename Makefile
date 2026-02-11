CC=gcc
CFLAGS=-Wall -Wextra

bridge: main.o
	$(CC) -fanalyzer -o $@ main.o

main.o: main.c
	$(CC) -c main.c

clean:
	rm bridge main.o
