/*
Arreglos Lea el archivo /proc/version y copie las palabras en un arreglo dinámico. Luego:

Imprima la lista de palabras en mayúscula.
libere la memoria que haya alocado.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 

#define SIZE 400
#define LIMIT " "


int main (int argc, char const *argv[])
{
    char buffer[SIZE]; 
    char *dbuffer;
    char **wdbuffer = NULL;
    char *token;
    FILE *file;

    file = fopen ("/proc/version","r");              // modo lectura
    if (file == NULL){
        perror("Error");
        return EXIT_FAILURE;
    }
            
    fgets(buffer, SIZE, file);                                                       // almaceno en buffer
    strtok(buffer, "\n");                                                                   // separar por salto
    size_t length = strlen(buffer);                                                         // obtengo longitud 
    if (length==0){
        printf("no hay lineas para procesar...\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    dbuffer = (char*) malloc(sizeof(char) * (length + 1));
    if (dbuffer == NULL) {
        perror("Error al reservar memoria");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++){
        dbuffer[i] = toupper(buffer[i]);
    }
    dbuffer[length] = '\0'; // null-terminate the string
   
    token = strtok(dbuffer, LIMIT);
    size_t index = 0;
    while( token != NULL ) {                                                    //tengo el tamaño de la palabra
        wdbuffer = (char **)realloc(wdbuffer,(sizeof(char *))*(index + 1));       //le asigno el espacio para apuntar al primer char
        if (wdbuffer == NULL) {
            perror("Error al reservar memoria");
            free(dbuffer);
            fclose(file);
            return EXIT_FAILURE;
        }
        wdbuffer[index] = strdup(token); // duplicar el token y asignar la direccion al puntero
        if (wdbuffer[index] == NULL) {
            perror("Error al reservar memoria");
            free(dbuffer);
            for (size_t i = 0; i < index; i++) {
                free(wdbuffer[i]);
            }
            free(wdbuffer);
            fclose(file);
            return EXIT_FAILURE;
        }
        token = strtok(NULL, LIMIT);
        index++;
    }
    size_t acc = 0;

	for(size_t j = 0; j<index ;j++){
		printf("[%ld] '%s' \n",strlen(wdbuffer[j]) + 1 ,wdbuffer[j]);
        free(wdbuffer[j]);
        acc+=strlen(wdbuffer[j]) + 1;
	}

    printf("tamanio total del symbols dynamic buffer: [%ld] \n",acc);

	fclose (file);
    free(dbuffer);
    free(wdbuffer);
    return EXIT_SUCCESS;
}
