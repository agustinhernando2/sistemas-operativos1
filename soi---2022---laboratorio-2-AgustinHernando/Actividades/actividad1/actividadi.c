/*
C-strings Realice las siguientes actividades:

Obtener la memoria ram total, libre y disponible en Megabytes. A partir del archivo /proc/meminfo.
Obtener la memoria swap Ocupada. A partir del archivo /proc/meminfo.
Crear un programa en C que imprima información referida al CPU, a partir del archivo /proc/cpuinfo:
Modelo de CPU.
Cantidad de cores
Cantidad de thread por cores.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getValueInMB (char *);
void removeSpaces (char *);

int main (int argc, char const *argv[])
{
                                                                        //busco y leo el archivo meminfo 
    FILE *pFile;                            
    pFile = fopen ("/proc/meminfo","r");
    if (pFile==NULL){
        perror("Error");
        return EXIT_FAILURE;
    }
                                                                        //defino variables que seran de ayuda
    char buffer[70];
	double MemTotal;
	double MemFree;
    double MemAvailable;
    double SwapTotal;
	double SwapFree;

    char *token;
                                                                        //extraigo cada linea del archivo y la proceso por separado
	while(fgets(buffer,70,pFile)){
                                                                        //separo cada linea por los espacios  
        token =strtok(buffer, " ");
        while( token != NULL ) {                                        //tomo cada cadena de texto hasta llegar a la ultima
            //printf( " %s\n", token );

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
            if(strcmp(token,"SwapTotal:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapTotal = atof(token)/1024;
                //printf("SwapTotal: %i MB\n",SwapTotal);
            }
            if(strcmp(token,"SwapFree:") == 0){
                token = strtok(NULL, " ");
                removeSpaces(token);
                SwapFree = atof(token)/1024;
                //printf("SwapFree: %i MB\n",SwapFree);
            }
            token = strtok(NULL, " ");
        }
    }
    double SwapOcupada = SwapTotal - SwapFree;

	

    printf("----/proc/meminfo:----\n");
    printf("MemTotal:         %.2f MB\n",MemTotal);
    printf("MemFree:          %.2f MB\n",MemFree);
    printf("MemAvailable:     %.2f MB\n",MemAvailable);
    printf("SwapOcupada:      %.2f mb\n",SwapOcupada);

    fclose(pFile); //Cierra el archivo
    printf("----/proc/cpuinfo:----\n");


    pFile = fopen ("/proc/cpuinfo","r");
    if (pFile==NULL){
        printf("No se pudo abrir el archivo.\n");
        return EXIT_FAILURE;
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
	
    printf("Modelo de CPU:             %s \n", model);
    printf("Cantidad de cores:                %d \n",nCores);
    printf("Cantidad de thread por cores:     %d \n",siblings);
   
    return EXIT_SUCCESS;
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