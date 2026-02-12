CC=gcc
CFLAGS=-Wall -Wextra

bridge: main.o cards.o
	$(CC) -fanalyzer -o $@ main.o cards.o

cards.o: defs.h cards.h cards.c
	$(CC) -fanalyzer -c cards.c

main.o: main.c cards.o
	$(CC) -fanalyzer -c main.c

clean:
	rm bridge main.o cards.o
