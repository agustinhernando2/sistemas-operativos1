/**
 * @file actividad_ii.c
 *
 * 2. Static Library
 * Implementar en el proyecto la librería cJSON, que permita:
 *
 * 2.1. Si se agrega, junto a las opciones del punto 1, la opción -j,
 * se debe utilizar la librería estática cJSON [1] y mostrar el resultado en dicho formato.


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
// #include "cJSON.h"
#include "actividadii.h"

int main(int argc, char **argv)
{
    int opt = 0;
    int activity1_1Flag = 0;
    int activity1_2Flag = 0;
    int activity1_3Flag = 0;
    int activity2Flag = 0;
    int jsonFlag = 0;

    // obtenemos los valores de la linea de comando (numero de arg, arg, condicion)
    while ((opt = getopt(argc, argv, "asj")) != -1)
        switch (opt)
        {
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
        case '?':
            fprintf(stderr, "Usage: %s [-s] [-a] [-j] \n", argv[0]); // sintaxis para introducir los datos
            exit(EXIT_FAILURE);
        }
    // SINTAXIS
    if (optind < argc || ((!activity1_1Flag) & (!activity1_2Flag) & (!activity1_3Flag) & (!activity2Flag)))
    {
        fprintf(stderr, "Unexpected argument after options\n"); // sintaxis para introducir los datos
        fprintf(stderr, "Usage: %s [-s] [-a] [-j] \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (activity1_1Flag && jsonFlag && activity2Flag)
    {
        printf("\n\nCopy and paste the json to validate format:\n https://jsonformatter.org/\n\n{\n\"activity_1\": ");
    }
    if (activity1_1Flag)
    {
        actividad1_1(jsonFlag);
        activity1_1Flag = 0;
    }
    if (activity1_2Flag)
    {
        actividad1_2(jsonFlag);
        activity1_2Flag = 0;
    }
    if (activity1_3Flag)
    {
        actividad1_3(jsonFlag);
        activity1_3Flag = 0;
    }
    if (activity1_1Flag && jsonFlag && activity2Flag)
    {
        printf(",\n\"activity_2\": [\n");
    }
    if (activity2Flag)
    {
        if (actividad2(jsonFlag))
        {
            fprintf(stderr, "Error en la actividad 2\n");
            return EXIT_FAILURE;
        }
        activity2Flag = 0;
    }
    if (activity1_1Flag && jsonFlag && activity2Flag)
    {
        printf("\n]\n}\n\n\n");
    }
    activity1_1Flag = 0;
    activity1_2Flag = 0;
    activity1_3Flag = 0;
    activity2Flag = 0;
    exit(EXIT_SUCCESS);
}

int actividad2(int json)
{
    char buffer[SIZE];
    char *dbuffer;
    char **wdbuffer = NULL;
    char *token;
    FILE *file;

    file = fopen("/proc/version", "r"); // modo lectura
    if (file == NULL)
    {
        printf("No se pudo abrir el file.\n");
        return 1;
    }

    fgets(buffer, SIZE, file); // almacenando cada línea
    strtok(buffer, "\n");      // separar por salto
    // printf("/proc/version: SIZE del buffer %ld\n'%s'\n",sizeof(buffer) ,buffer);        // imprimo contenido
    size_t length = strlen(buffer); // obtengo longitud
    if (length == 0)
    {
        printf("no hay lineas para procesar...\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    dbuffer = (char *)malloc(sizeof(char) * (length + 1));
    if (dbuffer == NULL)
    {
        perror("Error al reservar memoria");
        fclose(file);
        return 1;
    }

    for (size_t i = 0; i < length; i++)
    {
        dbuffer[i] = toupper(buffer[i]);
    }

    token = strtok(dbuffer, LIMIT);
    size_t index = 0;
    while (token != NULL)
    {                                                                          // tengo el tamaño de la palabra
        wdbuffer = (char **)realloc(wdbuffer, (sizeof(char *)) * (index + 1)); // le asigno el espacio para apuntar al primer char
        if (wdbuffer == NULL)
        {
            perror("Error al reservar memoria");
            free(dbuffer);
            fclose(file);
            return 1;
        }
        wdbuffer[index] = strdup(token); // duplicar el token y asignar la direccion al puntero
        if (wdbuffer[index] == NULL)
        {
            perror("Error al reservar memoria");
            free(dbuffer);
            for (size_t i = 0; i < index; i++)
            {
                free(wdbuffer[i]);
            }
            free(wdbuffer);
            fclose(file);
            return 1;
        }
        token = strtok(NULL, LIMIT);
        index++;
    }
    if (json)
    {
        jsonFormatterWordAndVersion(wdbuffer, index, buffer);
    }
    else
    {
        printf("/proc/version: '%s'\n", buffer);
        size_t acc = 0;
        for (size_t j = 0; j < index; j++)
        {
            printf("[%ld] '%s' \n", strlen(wdbuffer[j]) + 1, wdbuffer[j]);
            free(wdbuffer[j]);
            acc += strlen(wdbuffer[j]) + 1;
        }
        printf("tamanio total del word dynamic buffer: [%ld] \n", acc);
    }
    fclose(file);
    free(dbuffer);
    free(wdbuffer);
    return 0;
}
void actividad1_1(int json)
{
    FILE *pFile;
    pFile = fopen("/proc/meminfo", "r");
    if (pFile == NULL)
    {
        fprintf(stderr, "No se pudo abrir el file.\n");
        return;
    }
    // defino variables que seran de ayuda
    char buffer[70];
    double MemTotal;
    double MemFree;
    double MemAvailable;

    char *token;
    // extraigo cada linea del file y la proceso por separado
    while (fgets(buffer, 70, pFile))
    {
        // separo cada linea por los espacios
        token = strtok(buffer, " ");
        while (token != NULL)
        { // tomo cada cadena de texto hasta llegar a la ultima

            if (strcmp(token, "MemTotal:") == 0)
            {                              // si el texto esta relacionado con memTotal entonces proceso los numeros que estan asociados al dato
                token = strtok(NULL, " "); // cada vez que llamo a esta funcion se obtiene la siguiente cadena de texto que le sigue a un espacio " "
                removeSpaces(token);       // al remover espacios podemos pasar el string a numero float con atof
                MemTotal = atof(token) / 1024;
            }
            if (strcmp(token, "MemFree:") == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);
                MemFree = atof(token) / 1024;
            }
            if (strcmp(token, "MemAvailable:") == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);
                MemAvailable = atof(token) / 1024;
            }
            token = strtok(NULL, " ");
        }
    }

    if (json)
    {

        double value[3] = {
            MemTotal,
            MemFree,
            MemAvailable};
        printf("[\n");
        jsonFormatterMemInfo(value, actividad1_1_1, sizeof(value) / sizeof(double), " ");
        printf(",");
    }
    else
    {
        printf("----/proc/meminfo:----\n");
        printf("MemTotal:         %.2f MB\n", MemTotal);
        printf("MemFree:          %.2f MB\n", MemFree);
        printf("MemAvailable:     %.2f MB\n", MemAvailable);
    }

    fclose(pFile); // Cierra el file
}
void actividad1_2(int json)
{
    FILE *pFile;
    pFile = fopen("/proc/meminfo", "r");
    if (pFile == NULL)
    {
        fprintf(stderr, "No se pudo abrir el file.\n");
        return;
    }
    // defino variables que seran de ayuda
    char buffer[70];
    double SwapTotal;
    double SwapFree;
    char *token;
    // extraigo cada linea del file y la proceso por separado
    while (fgets(buffer, 70, pFile))
    {
        token = strtok(buffer, " "); // separo cada linea por los espacios
        while (token != NULL)
        { // tomo cada cadena de texto hasta llegar a la ultima
            if (strcmp(token, "SwapTotal:") == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapTotal = atof(token) / 1024;
            }
            if (strcmp(token, "SwapFree:") == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapFree = atof(token) / 1024;
            }
            token = strtok(NULL, " ");
        }
    }

    double SwapOcupada = SwapTotal - SwapFree;

    if (json)
    {
        double value[1] = {
            SwapOcupada};

        jsonFormatterMemInfo(value, actividad1_1_2, sizeof(value) / sizeof(double), " ");
        printf(",");
    }
    else
    {
        printf("----/proc/meminfo:----\n");
        printf("SwapOcupada:      %.2f MB\n", SwapOcupada);
    }
    fclose(pFile); // Cierra el file
}
void actividad1_3(int json)
{
    // busco y leo el file meminfo
    FILE *pFile; // defino variables que seran de ayuda
    char buffer[70];
    char *token;
    // extraigo cada linea del file y la proceso por separado
    pFile = fopen("/proc/cpuinfo", "r");
    if (pFile == NULL)
    {
        printf("No se pudo abrir el file.\n");
        return;
    }

    char *model = NULL;
    int nCores = 0;
    int siblings = 0;

    while (fgets(buffer, 70, pFile))
    {
        token = strtok(buffer, ":");
        while (token != NULL)
        {
            // printf( " %s\n", token );
            if (strstr(buffer, "model name") && model == NULL)
            {
                token = strtok(NULL, "");
                model = malloc(sizeof(char) * strlen(token));
                strcpy(model, token);
            }
            if (strstr(buffer, "siblings") && siblings == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);

                siblings = atoi(token);
            }
            if (strstr(buffer, "cpu cores") && nCores == 0)
            {
                token = strtok(NULL, " ");
                removeSpaces(token);
                nCores = atoi(token);
            }
            token = strtok(NULL, ":");
        }
    }

    siblings /= nCores;
    if (json)
    {
        double value[2] = {
            nCores,
            siblings};
        jsonFormatterMemInfo(value, actividad1_1_3, sizeof(value) / sizeof(double), model);
        printf("\n]\n");
    }
    else
    {
        printf("----/proc/cpuinfo:----\n");
        printf("Modelo de CPU:             %s", model);
        printf("Cantidad de cores:                %d \n", nCores);
        printf("Cantidad de thread por cores:     %d \n", siblings);
    }
    fclose(pFile);
}
int getValueInMB(char *a)
{ // recibo el char ejemplo "         123123123 kB" con espacios
    int value;
    char *token = strtok(a, " "); // cada vez que llamo a esta funcion me retorna un char limitado por " "
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
        { // cuando es mayor a uno ese char es porque no es un espacio
            value = atoi(token);
            value = value;
            token = strtok(NULL, " ");
            break;
        }
        token = strtok(NULL, " ");
    }
    return value;
}
void removeSpaces(char *a)
{                                 // recibo el char ejemplo "         123123123 kB" con espacios
    char *token = strtok(a, " "); // cada vez que llamo a esta funcion me retorna un char limitado por " "
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
        { // cuando es mayor a uno ese char es porque no es un espacio
            strcpy(a, token);
        }
        token = strtok(NULL, " ");
    }
}
