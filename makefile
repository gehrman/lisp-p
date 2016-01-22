# Most, if not all, of this is pulled right out of Klemen's 21st Century C.
CFLAGS=-Wall -std=c99
CC=clang

repl:
	$(CC) $(CFLAGS) -ledit src/repl.c -o repl
