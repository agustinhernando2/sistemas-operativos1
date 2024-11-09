CFLAGS = -Wall -Werror -pedantic 
EXEC = actividadii
OBJS = jsonformatter.o cJSON.o  actividadii.o libstatic.a
 
default: $(EXEC) 
 
$(EXEC): actividadii.o libstatic.a 
	$(CC) $(CFLAGS) -o $(EXEC) actividadii.o -L. -lstatic 
 
actividadii.o: actividadii.c
	$(CC) $(CFLAGS) -o actividadii.o -c actividadii.c 

libstatic.a: cJSON.o jsonformatter.o
	ar cr libstatic.a cJSON.o jsonformatter.o
 
cJSON.o: cJSON.c cJSON.h 
	$(CC) $(CFLAGS) -o cJSON.o -c cJSON.c 
	
jsonformatter.o: cJSON.c cJSON.h 
	$(CC) $(CFLAGS) -o jsonformatter.o -c jsonformatter.c 
 
clean: 
	rm -f *.o $(EXEC) $(OBJS)

clean2: 
	rm -f $(OBJS)
