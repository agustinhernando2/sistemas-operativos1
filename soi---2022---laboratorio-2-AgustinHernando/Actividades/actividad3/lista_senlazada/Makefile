CFLAGS = -Wall -Werror -pedantic 
EXEC = lista_senlazada 

default: $(EXEC) 
 
$(EXEC): lista_senlazada.c 
	$(CC) $(CFLAGS) -o $(EXEC) lista_senlazada.c 
 
clean: 
	rm -f *.o $(EXEC)
