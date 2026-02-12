CC=gcc
CFLAGS=-Wall -Wextra

bridge: main.o cards.o game.o
	$(CC) -fanalyzer -o $@ main.o cards.o game.o

game.o: defs.h cards.h game.h game.c
	$(CC) -fanalyzer -c game.c

cards.o: defs.h cards.h cards.c
	$(CC) -fanalyzer -c cards.c

main.o: main.c cards.o
	$(CC) -fanalyzer -c main.c

clean:
	rm bridge main.o cards.o game.o
