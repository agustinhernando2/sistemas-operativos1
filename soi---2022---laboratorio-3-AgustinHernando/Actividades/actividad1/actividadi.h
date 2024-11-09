#define FLAG
#ifdef FLAG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> 

#define SIZE 400
#define LIMIT " "

const char meminfo[20] = "/proc/meminfo";

const char cpuinfo[20] = "/proc/cpuinfo";

int getValueInMB (char *);
void removeSpaces (char *);
void actividad1_1();
void actividad1_2();
void actividad1_3();
int actividad2();
#endif