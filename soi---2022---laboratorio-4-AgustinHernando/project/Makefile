CC=gcc
CFLAGS= -Wall -pedantic -Werror -Iinclude

EXEC = gushgush

bin/myshellbasic: src/myshellbasic.o src/functions.o
	$(CC) $(CFLAGS) src/myshellbasic.o src/functions.o -o bin/$(EXEC)

src/myshellbasic.o: src/myshellbasic.c include/functions.h
	$(CC) $(CFLAGS) -c src/myshellbasic.c -o src/myshellbasic.o

src/functions.o: src/functions.c include/functions.h
	$(CC) $(CFLAGS) -c src/functions.c -o src/functions.o

clean:
	rm -f bin/* src/*.o
