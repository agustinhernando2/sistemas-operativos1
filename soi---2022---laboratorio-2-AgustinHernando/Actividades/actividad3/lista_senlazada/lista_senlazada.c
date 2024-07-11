#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista_senlazada.h"


nodo* enlazarSig(nodo*, char*);
void imprimirLista(nodo*);

int main(){
    char str[50];
    char *text;
    nodo *lista = NULL;
    int amount = 0;

    printf("Cuantos elementos desea agregar a la lista?:");
    scanf("%d", &amount);


    for (size_t i = 0; i < amount; i++){
        printf( "Escriba y agregue a la lista: ");
        scanf("%s", str);
        text = (char*) malloc(sizeof(char)*strlen(str));
        for (size_t i = 0; i < strlen(str); i++){text[i] = str[i];}
        lista = enlazarSig(lista,text);
    }

    printf("\nLISTA:\n");
    imprimirLista(lista);
    
    // free memory
    while(lista != NULL){
        nodo *aux = lista;
        lista = lista->sig;
        free(aux->dato);
        free(aux);
    }

    return EXIT_SUCCESS;
}   

nodo* enlazarSig(nodo *lista, char *dato){
	nodo *nuevo, *aux;
	nuevo = (nodo*)malloc(sizeof(nodo)); 
	nuevo->dato = dato;
	nuevo-> sig = NULL;

	if(lista == NULL){	
		lista = nuevo;                      //Es el primer elemento de la lista
	}else{
		aux = lista;
		while(aux->sig != NULL){
			aux = aux -> sig;               //Es el ultimo elemento de la lista    
		}
		aux -> sig = nuevo;                 //Agrega el nodo al final de la lista
	}
	return lista;
}
void imprimirLista(nodo *lista){
    while(lista != NULL){
		printf("%s\n",lista->dato);
		lista = lista->sig;
	}
}