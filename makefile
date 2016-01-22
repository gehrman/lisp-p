# Most, if not all, of this is pulled right out of Klemen's 21st Century C.
CFLAGS=-Wall -std=c99
CC=clang

repl:
	$(CC) $(CFLAGS) src/repl.c extern/mpc/mpc.c -ledit -lm -o repl

parser:
	$(CC) $(CFLAGS) src/parser.c extern/mpc/mpc.c -lm -o parser
