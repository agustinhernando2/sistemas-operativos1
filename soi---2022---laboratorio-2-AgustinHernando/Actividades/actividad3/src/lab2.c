#include <stdio.h>
#include "structs.h"

int main()
{
    /* Explique a que se debe los tamanios de cada una de las estructuras */
    printf("base     struct size  %lu \n", sizeof(BaseData));
    printf("reorder  struct size  %lu \n", sizeof(ReorderData));
    printf("extended struct size  %lu \n", sizeof(ExtendedData));
    printf("packed   struct size  %lu \n\n", sizeof(BaseDataPacked));

    /* explique por que la expresion que calcula  limit y limit_aux generan el mismo resutado */
    /* hint : investigar sobre reglas de aritmetica de punteros */
    /* no entiendo porque *limit = &data no me da la misma direccion  */
    /* el compilador se da cuenta que debe avanzar en +1 como si fuera un array y si lo pones con sizeof() queda explicito*/
    const BaseData data = {
                .a = 1,
                .b = 3,
                .x = 15,
                .y = 65535,
                .c = -128,
                .z = -1, 
                .d = {1,1,1,1}
    };
    printf("tamaño char :%02ld\n",sizeof(char));
    printf("tamaño int :%02ld\n",sizeof(int));
    printf("tamaño unsigned short int :%02ld\n",sizeof(unsigned short int));
    printf("tamaño char d[3] :%02ld\n",3*sizeof(char));
    printf("tamaño long unsigned int :%02ld\n",sizeof(long unsigned int));


    printf("address memory %p \n",&data.a );

    char *limit = ((char *) &data + sizeof(BaseData)); 
    char *limit_aux =(char *) (&data + 1);

    printf("limit     value is %p \n", limit); 
    printf("limit_aux value is %p \n\n", limit_aux); 

    int i = 0;
    /* Explique los valores que se muestran en pantalla en cada iteracion del for */
    for (char *c = (char *) &data; c < limit; c++, i++ ){
        //printf("current is              %p \n", c); 
        printf("byte %02d : 0x%02hhx \n", i, *c);
    }
    /* el resultado en consola muestra la distribucion de las variables en memoria
    01 03 00 00    0f 00 00 00    ff ff 80 ff    ff ff 01 01    01 01 00 00   
    |a||b| *  *   |     x     |   | y ||c | *    | z  ||     d       | *  *
    
    */
}
