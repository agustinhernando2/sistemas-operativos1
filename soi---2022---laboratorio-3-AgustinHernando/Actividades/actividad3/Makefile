CFLAGS = -Wall -Werror -pedantic 
EXEC = actividadiii
OBJS = cJSON.o actividadiii.o libfilesystem.so actividad.elf
 
default: $(EXEC) 
 
$(EXEC): actividadiii.c libfilesystem.so cJSON.c
	$(CC) $(CFLAGS) -o actividad.elf actividadiii.c cJSON.c -ldl
 
libfilesystem.so: libfilesystem.c cJSON.c
	$(CC) -shared -fPIC -o libfilesystem.so libfilesystem.c cJSON.c

clean: 
	rm -f *.o $(EXEC) $(OBJS)

clean2: 
	rm -f $(OBJS)