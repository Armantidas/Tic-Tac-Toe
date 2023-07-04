CC=gcc
CFLAGS=-I.
DEPS = dataFile.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tictactoe: main.o dataFile.o
	$(CC) -o tictactoe main.o dataFile.o
