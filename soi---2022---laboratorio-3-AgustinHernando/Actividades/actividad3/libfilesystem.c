#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

FILE* abrirArchivo(){
	FILE *archivo = NULL;
	archivo = fopen("/proc/filesystems","r");
	if(archivo == NULL){
		printf("Fallo abrir el archivo.\n");
		exit(EXIT_FAILURE);
	}
	return archivo;
}

void filesystemsCJSON(){
	FILE *archivo;
	archivo = abrirArchivo();
	
    cJSON *information = cJSON_CreateString("/proc/filesystems");
	if (information == NULL){goto end;}

	cJSON *json = cJSON_CreateObject();
	if (json == NULL){goto end;}
	cJSON_AddItemToObject(json, "path", information);


    cJSON *data = cJSON_CreateArray();
	if (data == NULL){goto end;}
	
	char row[20];
	while(fgets(row,sizeof(row),archivo)){
		char *token = strtok(row,"\t\n");
		char current[30] = "";
		
		if (strstr(row, "nodev")) {  
            strcpy(current, "nodev ");
            token = strtok(NULL, "\t\n"); 
            if (token != NULL) {
                strcat(current, token); 
            }
        } else {  
            strcpy(current, "      ");
            if (token != NULL) {
                strcat(current, token);  
            }
        }
        cJSON_AddItemToArray(data, cJSON_CreateString(current)); 
	}
    cJSON_AddItemReferenceToObject(json,"data",data);

	char *imprimir = cJSON_Print(json);
end:
	printf("%s\n",imprimir);
	cJSON_Delete(json);
	fclose(archivo);
}
