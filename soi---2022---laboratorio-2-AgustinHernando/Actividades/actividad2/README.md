# Actividad 2
## _Arreglos_
Lea el archivo `/proc/version` y copie las palabras en un arreglo dinámico.
Luego:
   1. Imprima la lista de palabras en mayúscula. 
   2. libere la memoria que haya alocado.

## Archivo `/proc/version` 
El archivo /proc/version contiene una línea de texto que proporciona información sobre la versión del kernel de Linux, el compilador utilizado, y la fecha de compilación. Un ejemplo del contenido del archivo es:
```bash
Linux version 5.4.0-42-generic (buildd@lcy01-amd64-021) (gcc version 9.3.0 (Ubuntu 9.3.0-10ubuntu2)) #46-Ubuntu SMP Fri Jul 10 05:46:45 UTC 2020
```
## Modo de ejecución

```bash
make
./actividadii
valgrind --leak-check=full ./actividadii
```

## Resultado
Ejecucion
```bash
[6] 'LINUX' 
[8] 'VERSION' 
[17] '6.5.0-41-GENERIC' 
[25] '(BUILDD@LCY02-AMD64-120)' 
[25] '(X86_64-LINUX-GNU-GCC-12' 
[8] '(UBUNTU' 
[23] '12.3.0-1UBUNTU1~22.04)' 
[8] '12.3.0,' 
[4] 'GNU' 
[3] 'LD' 
[5] '(GNU' 
[9] 'BINUTILS' 
[4] 'FOR' gi
[8] 'UBUNTU)' 
[6] '2.38)' 
[19] '#41~22.04.2-UBUNTU' 
[4] 'SMP' 
[16] 'PREEMPT_DYNAMIC' 
[4] 'MON' 
[4] 'JUN' 
[2] '3' 
[9] '11:32:55' 
[4] 'UTC' 
[2] '2' 
tamanio total del symbols dynamic buffer: [166]
```

Valgrind
```bash
==22027== HEAP SUMMARY:
==22027==     in use at exit: 0 bytes in 0 blocks
==22027==   total heap usage: 52 allocs, 52 frees, 5,367 bytes allocated
==22027== 
==22027== All heap blocks were freed -- no leaks are possible
==22027== 
==22027== For lists of detected and suppressed errors, rerun with: -s
==22027== ERROR SUMMARY: 223 errors from 2 contexts (suppressed: 0 from 0)
```