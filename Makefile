# Compiler Basics
CC = gcc
CFLAGS = -fanalyser
CWARN = -Wall -Werror -Wextra

# Source & objects
SRCS = cards.c game.c main.c
OBJS = $(SRCS:.c=.o)
BIN = bridge

# Buid settings
OUTDIR = build
DBGDIR = debug
BUILDDIR =


DEBUG?=0
ifeq ($(DEBUG), 1)
    CFLAGS :=  $(CFLAGS) -g
    BUILDDIR = $(DBGDIR)
else
    BUILDDIR = $(OUTDIR)
endif

BIN := $(BUILDDIR)/$(BIN)i
CC := $(CC) $(CFLAGS)

.PHONY: all

all: $(BIN)

$(BIN): $(OBJS)
	mkdir -p $(BUILDDIR)
	$(CC) -o $@ $^ $(CWARN)

%.o: %.c
	$(CC) -c $(SRCS)

.PHONY: clean

clean:
	rm -f $(BIN) $(OBJS)
	rmdir $(BUILDDIR)
