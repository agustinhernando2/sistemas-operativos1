CFLAGS = -Wall -Werror -pedantic 
EXEC = actividad.elf
OBJS = cJSON.o actividadiii.o libfilesystem.so 
 
default: $(EXEC) 
 
$(EXEC): actividadiii.c libfilesystem.so cJSON.c
	$(CC) $(CFLAGS) -o $(EXEC) actividadiii.c cJSON.c -ldl  # -ldl enlaza la biblioteca libdl (dinámica)

libfilesystem.so: libfilesystem.c cJSON.c
	$(CC) -shared -fPIC -o libfilesystem.so libfilesystem.c cJSON.c  # Creación de una biblioteca compartida

clean: 
	rm -f *.o $(EXEC) $(OBJS)

clean2: 
	rm -f $(OBJS)
