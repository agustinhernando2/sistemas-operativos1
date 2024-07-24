/**
 * @file actividad_iii.c
 * 
 * 3 Dynamic Library
 * Se debe diseñar e implementar una librería dinámica que actúe como plugin, extendiendo las opciones y que permita lo siguiente:
 * 
 * 3.1. Se debe cargar dinámicamente al ejecutarse con la opción -d
 * 
 * 3.2. Debe mostrar, utilizando la librería cJSON del punto 2, la información sobre los filesystems soportado por el kernel en uso: /proc/filesystems.
 * 
 * 
 * @author Agustin Hernando (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> 
#include "cJSON.h"
#include <dlfcn.h>
#include "actividadiii.h"


int main(int argc, char **argv)
{   
    int opt = 0;
    int activity1_1Flag = 0;
    int activity1_2Flag = 0; 
    int activity1_3Flag = 0;
    int activity2Flag = 0;
    int actFileSystem = 0;
    int jsonFlag= 0; 

                                                                    //obtenemos los valores de la linea de comando (numero de arg, arg, condicion)
    while ((opt = getopt(argc,argv,"asjd")) != -1)
        switch(opt){
            case 'a':
                activity1_1Flag = 1;
                activity1_2Flag = 1;
                activity1_3Flag = 1;
                break;
            case 's':
                activity2Flag = 1;
                break;
            case 'j':
                jsonFlag = 1;
                break;   
            case 'd':
                actFileSystem = 1;
                break;  
            case '?':
                fprintf(stderr, "Usage: %s [-s] [-a] [-j] [-d]\n", argv[0]); //sintaxis para introducir los datos
                exit(EXIT_FAILURE);

        }
                                                                    // SINTAXIS
    if (optind < argc ||((!activity1_1Flag)&(!activity1_2Flag)&(!activity1_3Flag)&(!actFileSystem)&(!activity2Flag))) {
       fprintf(stderr, "Unexpected argument after options\n");      //sintaxis para introducir los datos
       fprintf(stderr, "Usage: %s [-s] [-a] [-j] [-d] \n", argv[0]);          
       exit(EXIT_FAILURE);
    }
    if((activity1_1Flag && jsonFlag && activity2Flag) ||
        (actFileSystem)){
        printf("\n\nCopy and paste the json to validate format:\n https://jsonformatter.org/\n");
       
    }
    if( (activity1_1Flag && jsonFlag && activity2Flag) ||
        (activity1_1Flag && jsonFlag && actFileSystem) ||
        (activity2Flag && jsonFlag && actFileSystem)                   ){
        printf("\n{\n");
    }
    if(actFileSystem){
        //abrir y usar libreria dinamica
         void *libhandle = dlopen("./libfilesystem.so",RTLD_LAZY);
        if(libhandle == NULL){
            printf("Usage: %s . -d \n",argv[0]);
            exit(EXIT_FAILURE);
        }
        printf("\n\"filesystems\":");
        void (*opfunc)();
        *(void **)(&opfunc) = dlsym(libhandle,"filesystemsCJSON");	//carga la función 

        (*opfunc)();
        dlclose(libhandle); 
    }
    if( (activity1_1Flag && jsonFlag && actFileSystem) ||
        (activity2Flag && jsonFlag && actFileSystem)                   ){
        printf(",\n");
    }
    if(activity1_1Flag){
        printf("\n\"activity_1\":");
        actividad1_1(jsonFlag);
    }
    if(activity1_2Flag){
        actividad1_2(jsonFlag);
    }
    if(activity1_3Flag){
        actividad1_3(jsonFlag);
    }
    if( (activity1_1Flag && jsonFlag && activity2Flag) ||
        (activity2Flag && jsonFlag && actFileSystem)                   ){
        printf(",\n");
    }

    if(activity2Flag){
        printf("\n\"activity_2\":");
        actividad2(jsonFlag);
    }
    if( (activity1_1Flag && jsonFlag && activity2Flag) ||
        (activity1_1Flag && jsonFlag && actFileSystem) ||
        (activity2Flag && jsonFlag && actFileSystem)                   ){
        printf("\n}\n");
       
    }
    activity1_1Flag = 0;
    activity1_2Flag = 0;
    activity1_3Flag = 0;
    activity2Flag = 0;
    actFileSystem = 0;

    exit(EXIT_SUCCESS);
}

void jsonFormatter(double value[], int flag, int n,char *info){
   
    char *json = NULL;
    cJSON *information = NULL;
    cJSON *dataJson = NULL;
    cJSON *item = NULL;
    cJSON *mem = NULL;


    cJSON *monitor = cJSON_CreateObject();
    if (monitor == NULL){goto end;}

    information = cJSON_CreateString(path_1);
    if (information == NULL){goto end;}

    if(flag==1||flag==2){
        information = cJSON_CreateString(path_1);
        if (information == NULL){goto end;}
        cJSON_AddItemToObject(monitor, "path", information);
    }else if(flag == 3){
        information = cJSON_CreateString(info);
        if (information == NULL){goto end;}
        cJSON_AddItemToObject(monitor, "model", information);
    }
    

    dataJson = cJSON_CreateArray();
    if (dataJson == NULL){goto end;}

    cJSON_AddItemToObject(monitor, "data", dataJson);
    for (int index = 0; index < n; ++index){
        item = cJSON_CreateObject();
        if (item == NULL){goto end;}
     
        cJSON_AddItemToArray(dataJson, item);

        mem = cJSON_CreateNumber(value[index]);
        if (mem == NULL){goto end;}
        if(flag==1){
            cJSON_AddItemToObject(item, data_1[index], mem);
        }else if(flag==2){
            cJSON_AddItemToObject(item, data_2[index], mem);
        }else if(flag==3){
            cJSON_AddItemToObject(item, data_3[index], mem);
        }
    }

    json = cJSON_Print(monitor);
    if (json == NULL){
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    printf("%s\n",json);
}
void jsonFormatter2(char ** words,int limit, char *version){
   
    char *json = NULL;
    cJSON *information = NULL;
    cJSON *dataJson = NULL;
    cJSON *item = NULL;


    cJSON *monitor = cJSON_CreateObject();
    if (monitor == NULL){goto end;}

    information = cJSON_CreateString(version);
    if (information == NULL){goto end;}
    cJSON_AddItemToObject(monitor, "vesion", information);
    
    dataJson = cJSON_CreateArray();
    if (dataJson == NULL){goto end;}

    cJSON_AddItemToObject(monitor, "words", dataJson);
    for (int index = 0; index < limit; ++index){
        item = cJSON_CreateString(words[index]);
        if (item == NULL){goto end;}
        cJSON_AddItemToArray(dataJson, item);
    }

    json = cJSON_Print(monitor);
    if (json == NULL){
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    printf("%s\n",json);
}

void actividad2(int json){
    char buffer[LONGITUD]; 
    char *dbuffer;
    char **wdbuffer = NULL;
    char *token;
    FILE *archivo;

    archivo = fopen ("/proc/version","r");              // modo lectura
    if (archivo==NULL){
        printf("No se pudo abrir el archivo.\n");
        return;
    }
            
    fgets(buffer, LONGITUD, archivo);                                                       //almacenando cada línea
    strtok(buffer, "\n");                                                                   // separar por salto
    //printf("/proc/version: longitud del buffer %ld\n'%s'\n",sizeof(buffer) ,buffer);        // imprimo contenido
    size_t length = strlen(buffer);                                                         // obtengo longitud 
    if (length==0){
        printf("no hay lineas para procesar...\n");
        return;
    }
    dbuffer = (char*) malloc(sizeof(char)*length);

    for (size_t i = 0; i < length; i++){
        dbuffer[i] = toupper(buffer[i]);
    }
    //printf("/proc/version:  longitud del buffer dinamico %ld\n'%s'\n",sizeof(dbuffer), dbuffer); 
   
    token = strtok(dbuffer, LIMIT);
    size_t index = 0;
    while( token != NULL ) {                                                //tengo el tamaño de la palabra
        wdbuffer = (char **)realloc(wdbuffer,(sizeof(char *))*(index+1));       //le asigno el espacio para apuntar al primer char
        wdbuffer [index] = (char *)malloc(strlen(token)*sizeof(char));          //le asigno el espacio para dejar espacio para los caracteres
        wdbuffer [index] = token;                                               //guardo palabra
        token = strtok(NULL, LIMIT);
        index++;
    }
    if(json){
        jsonFormatter2(wdbuffer,index, buffer);
    }else{
        printf("/proc/version: '%s'\n", buffer);
        size_t acc = 0;
        for(size_t j = 0; j<index ;j++){
            printf("[%ld] '%s' \n",strlen(wdbuffer[j]) + 1 ,wdbuffer[j]);
            acc+=strlen(wdbuffer[j]) + 1;
        } 
        printf("tamanio total del word dynamic buffer: [%ld] \n",acc);
    }
	fclose (archivo);
    free(dbuffer);
    free(wdbuffer);
}
void actividad1_1(int json){
    FILE *pFile;                            
    pFile = fopen ("/proc/meminfo","r");
    if (pFile==NULL){
        fprintf(stderr,"No se pudo abrir el archivo.\n");
        return;
    }
                                                                        //defino variables que seran de ayuda
    char buffer[70];
    double MemTotal;
    double MemFree;
    double MemAvailable;

    char *token;
                                                                        //extraigo cada linea del archivo y la proceso por separado
    while(fgets(buffer,70,pFile)){
                                                                        //separo cada linea por los espacios  
        token =strtok(buffer, " ");
        while( token != NULL ) {                                        //tomo cada cadena de texto hasta llegar a la ultima
            
            if(strcmp(token,"MemTotal:") == 0){                         //si el texto esta relacionado con memTotal entonces proceso los numeros que estan asociados al dato
                token = strtok(NULL, " ");                              //cada vez que llamo a esta funcion se obtiene la siguiente cadena de texto que le sigue a un espacio " "
                removeSpaces(token);                                    //al remover espacios podemos pasar el string a numero float con atof
                MemTotal = atof(token)/1024;                            
                
            }
            if(strcmp(token,"MemFree:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                MemFree = atof(token)/1024;
                
            }
            if(strcmp(token,"MemAvailable:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                MemAvailable = atof(token)/1024;
                
            }
            token = strtok(NULL, " ");
        }
    }

    if(json){

        double value[3] = {
            MemTotal,
            MemFree,
            MemAvailable
        };
        printf("[\n");
        jsonFormatter(value,actividad1_1_1,sizeof(value)/sizeof(double)," ");
        printf(",");
    }else{
        printf("----/proc/meminfo:----\n");
        printf("MemTotal:         %.2f MB\n",MemTotal);
        printf("MemFree:          %.2f MB\n",MemFree);
        printf("MemAvailable:     %.2f MB\n",MemAvailable);

    }

    fclose(pFile); //Cierra el archivo
}
void actividad1_2(int json){
    FILE *pFile;                            
    pFile = fopen ("/proc/meminfo","r");
    if (pFile==NULL){
        fprintf(stderr,"No se pudo abrir el archivo.\n");
        return;
    }
                                                                        //defino variables que seran de ayuda
    char buffer[70];
    double SwapTotal;
    double SwapFree;
    char *token;
                                                                        //extraigo cada linea del archivo y la proceso por separado
    while(fgets(buffer,70,pFile)){                      
        token =strtok(buffer, " ");                                     //separo cada linea por los espacios  
        while( token != NULL ) {                                        //tomo cada cadena de texto hasta llegar a la ultima
            if(strcmp(token,"SwapTotal:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapTotal = atof(token)/1024;
            }
            if(strcmp(token,"SwapFree:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapFree = atof(token)/1024;
            }
            token = strtok(NULL, " ");
        }
    }

    double SwapOcupada = SwapTotal - SwapFree;

    if(json){
        double value[1] = {
            SwapOcupada
        };
        
        jsonFormatter(value,actividad1_1_2,sizeof(value)/sizeof(double)," ");
        printf(",");
    }else{
        printf("----/proc/meminfo:----\n");
        printf("SwapOcupada:      %.2f MB\n",SwapOcupada);
    }
    fclose(pFile); //Cierra el archivo

}
void actividad1_3(int json){
                                                                        //busco y leo el archivo meminfo 
    FILE *pFile;                                                                //defino variables que seran de ayuda
    char buffer[70];
    char *token;
                                                                        //extraigo cada linea del archivo y la proceso por separado
    pFile = fopen ("/proc/cpuinfo","r");
    if (pFile==NULL){
        printf("No se pudo abrir el archivo.\n");
        return ;
    }
    
	char *model=NULL;
	int nCores = 0;
    int siblings = 0;
    
	while(fgets(buffer,70,pFile)){  
        token =strtok(buffer, ":");
        while( token != NULL ) {
            //printf( " %s\n", token );
            if(strstr(buffer,"model name") && model==NULL){
                token = strtok(NULL, "");
                model = malloc(sizeof(char)*strlen(token));
                strcpy(model,token);
            }
            if(strstr(buffer,"siblings") && siblings == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
  
                siblings = atoi(token);
            }
            if(strstr(buffer,"cpu cores") && nCores == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                nCores = atoi(token);
            }
            token = strtok(NULL, ":");
        }
    }

    siblings /= nCores;
     if(json){
        double value[2] = {
            nCores,
            siblings
        };
        jsonFormatter(value,actividad1_1_3,sizeof(value)/sizeof(double),model);
        printf("\n]\n");
    }else{
	printf("----/proc/cpuinfo:----\n");
    printf("Modelo de CPU:             %s", model);
    printf("Cantidad de cores:                %d \n",nCores);
    printf("Cantidad de thread por cores:     %d \n",siblings);
    }
    fclose(pFile); 
}
int getValueInMB (char *a){                     //recibo el char ejemplo "         123123123 kB" con espacios
    int value;
    char *token = strtok(a," ");                //cada vez que llamo a esta funcion me retorna un char limitado por " "
    while(token != NULL){
        if(strcmp(token," ")!=0){	                //cuando es mayor a uno ese char es porque no es un espacio
            value = atoi(token);    
            value = value;
            token = strtok(NULL," ");
            break;
        }
        token = strtok(NULL," ");
    }
    return value;
}
void removeSpaces (char *a){                     //recibo el char ejemplo "         123123123 kB" con espacios
    char *token = strtok(a," ");                //cada vez que llamo a esta funcion me retorna un char limitado por " "
    while(token != NULL){
        if(strcmp(token," ")!=0){	                //cuando es mayor a uno ese char es porque no es un espacio
            strcpy(a,token);    
        }
        token = strtok(NULL," ");
    }
}
