# Actividad 3
## _Estructuras_
### PRIMERA PARTE
#### _¿Cómo utilizar typedef junto a struct? ¿Para qué sirve? Ejemplo._
*typedef* es una palabra reservada de C y C++. Su función es asignar un nombre alternativo a tipos existentes. Utilizarlo en estructuras de datos nos permitiría "abreviarlas".
Por ejemplo:
```c
#include <stdio.h>

struct persona {
	char nombre [30];
	char apellido [30];
	char pais [30];	
};

typedef struct persona p;

int main(){
	p persona1;
	printf("Ingrese su nombre: ");
	gets(persona1.nombre);
	printf("Ingrese su apellido: ");
	gets(persona1.apellido);
	printf("Ingrese su pais: ");
	gets(persona1.pais);

	return EXIT_SUCCESS;
}
```

    

#### _¿Qué es packing and padding ?_
El procesador lee una palabra a la vez, el padding es un concepto de C que agrega bytes vacios 
entre las direcciones de memoria para alinear los datos.
Nunca va a haber padding inicial.
Mejora el rendimiento.

Por ejemplo:

```c
struct abc{
	char a;   //1 byte
  	int b;    //4 bytes
  	char c;   //1 byte
};
```

Siempre el tamaño es el del tipo de dato que más bytes ocupa

*x* representa un espacio vacío, *i* representa espacio para el integer, *c* espacio para el char
```sh
|c x x x|i i i i|c x x x |   =>12bytes    	(caso 1)
```

si reordenamos podemos comprimir este espacio que agrega el padding 
```c
struct abc{
	int b;    //4 bytes
	char a;   //1 byte
  	char c;   //1 byte
};
```
```sh
|i i i i|c c x x|  			=>8bytes		(caso 2)
```

El **packing** elimina el padding, alineando los elementos uno al lado del otro. Es decir:
```sh
|c i i i|i c x x|  	(caso 1)
|i i i i|c c x x|	(caso 2)
```
Generalmente se utiliza cuando tiene más prioridad el espacio en memoria que el acceso a memoria.

### SEGUNDA PARTE: A partir de los archivos struct.h y lab2.c, asociados a este laboratorio:
- Genere un binario a partir de dichos archivos el binario se encuentra en ./src/lab2
- Responda las 3 preguntas que aparecen comentadas en el código.

#### _A que se deben los tamaños de cada una de las estructuras?_

- *x* ..representa un espacio vacío.
- *i* ..representa espacio para el integer.
- *c* ..espacio para el char.
- *l* ..representa espacio para el unsigned short int.
- *L* ..representa espacio para el long unsigned int.
- *C* ..espacio para el char[].

**base     struct size  20**
```c
typedef struct {
    char a;						    1
    char b;						    1
    int  x;						    4
    unsigned short int y;	    	2
    char c;						    1
    unsigned short int z;			2
    char d[4];						4
} BaseData;
```

el dato mas grande ocupa 4 bytes => tenemos palabra de 4 bytes
```sh
|c c x x|i i i i|l l c x|l l x x|C C C C|		=>20  bytes
```

**reorder  struct size  16**
```c
typedef struct {
    char a;						    1
    char b;						    1
    int  x;						    4
    unsigned short int y;		    2
    unsigned short int z;		    2
    char c;						    1	
    char d[3];					    3
} ReorderData;						
```
el dato mas grande ocupa 4 bytes => tenemos palabra de 4 bytes

```sh
|c c x x|i i i i|l l l l|c C C C|			=>16 bytes
```

**extended struct size  24**
```c
typedef struct {
    long unsigned int ll;			8
    char a;						    1		
    char b;						    1
    unsigned short int y;			2
    int  x;						    4
    unsigned short int z;			2
    unsigned short int w;			2
    char c;						    1
    char d[3];						3
} ExtendedData;					
```
el dato mas grande ocupa 8 bytes => tenemos palabra de 8 bytes

```sh
|L L L L L L L L|c c l l i i i i|l l l l c C C C|	=>24 bytes
```

**packed   struct size  14**
```c
typedef struct  __attribute__((packed)) {
    char a;						    1	
    char b;						    1		
    int  x;						    4		
    unsigned short int y;			2		
    char c;						    1	
    unsigned short int z;			2
    char d[3];						3			
} BaseDataPacked;				
```

el dato mas grande ocupa 4 bytes => tenemos palabra de 4 bytes
```sh
|c c x x| i i i i| l l c x | l l x x x| C C C x|	=>20 bytes
```
pero como tiene __attribute__((packed)), entonces se elimina el padding:
```sh
|c c i i| i i l l|c l l C|C C x x|			=>14 bytes
```

## TERCERA PARTE: Crear una lista simplemente enlazada
_Escribir una función que permita agregar un nodo al final de la lista_

### Modo de ejecución

```bash
make
./lista_senlazada
valgrind --leak-check=full ./lista_senlazada
```

### Resultado
Ejecucion
```bash
./lista_senlazada
Cuantos elementos desea agregar a la lista?:10
Escriba y agregue a la lista: A
Escriba y agregue a la lista: C
Escriba y agregue a la lista: D
Escriba y agregue a la lista: V
Escriba y agregue a la lista: 1
Escriba y agregue a la lista: 2
Escriba y agregue a la lista: 11
Escriba y agregue a la lista: 10
Escriba y agregue a la lista: 09
Escriba y agregue a la lista: AGUSTIN

LISTA:
A
C
D
V
1
2
11
10
09
AGUSTIN
```

Valgrind
```bash
==37523== HEAP SUMMARY:
==37523==     in use at exit: 0 bytes in 0 blocks
==37523==   total heap usage: 12 allocs, 12 frees, 2,133 bytes allocated
==37523== 
==37523== All heap blocks were freed -- no leaks are possible
==37523== 
==37523== For lists of detected and suppressed errors, rerun with: -s
==37523== ERROR SUMMARY: 5 errors from 1 contexts (suppressed: 0 from 0)
```