#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <ctype.h> 
#include "cJSON.h"

const char data_1[3][25] = {
    "Memoria Total[MB]",
    "Memoria Free[MB]",
    "Memoria Available[MB]"
};
const char path_1[20] = "/proc/meminfo";

const char data_2[1][25] = {
    "SwapOcupada [MB]"
};
const char path_2[20] = "/proc/meminfo";

const char data_3[2][25] = {
            "Cantidad_de_cores",
            "thread_por_cores"
        };
const char information_3[20] = "model";

/**
 * @brief Formatea un arreglo a JSON.
 * Genera un JSON con un campo "path" o "model" y una lista de datos
 * 
 * @param value Array
 * @param flag 1 para data_1, 2 para data_2, 3 para data_3.
 * @param n
 * @param info para flag = 3.
 */
void jsonFormatterMemInfo(double value[], int flag, int n,char *info){
   
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


/**
 * @brief Formatea Array de palabras y versión en JSON.
 * 
 * @param words Array de palabras.
 * @param limit Cantidad de palabras.
 * @param version version.
 */
void jsonFormatterWordAndVersion(char ** words,int limit, char *version){
   
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
