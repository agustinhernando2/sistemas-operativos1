CC=gcc
CFLAGS= -Wall -pedantic -Werror

EXEC = gushgush

bin/myshellbasic: src/myshellbasic.c src/functions.c
	$(CC) $(CFLAGS) src/myshellbasic.c -o bin/${EXEC}

clean:
	rm -f bin/* 
