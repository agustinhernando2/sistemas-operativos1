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


    cJSON *data = cJSON_CreateObject();
	if (data == NULL){goto end;}
	char array [20];
	int cont = 0;
	while(fgets(array,sizeof(array),archivo)){
		char *token = strtok(array,"\t\n");
		if(strstr(array,"nodev")){  						//busca los renglones del archivo que comienzan con nodev
			while(token != NULL){
				if(cont == 1){
					cJSON_AddStringToObject(data,"nodev",token);
				}
				cont ++;
				token = (strtok(NULL,"\t\n"));
			}
			cont = 0;
		}else{
			while(token != NULL){
				cJSON_AddStringToObject(data,"     ",token);
				token = (strtok(NULL,"\t\n"));
			}
		}
	}
    cJSON_AddItemReferenceToObject(json,"data",data);



	char *imprimir = cJSON_Print(json);
end:
	printf("%s\n",imprimir);
	cJSON_Delete(json);
	fclose(archivo);
}
