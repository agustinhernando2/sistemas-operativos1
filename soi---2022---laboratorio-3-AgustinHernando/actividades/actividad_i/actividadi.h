#define FLAG
#ifdef FLAG
#define LONGITUD 200
#define LIMIT " "
#define actividad1_1_1 1
#define actividad1_1_2 2
#define actividad1_1_3 3

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

int getValueInMB (char *);
void removeSpaces (char *);
void actividad1_1();
void actividad1_2();
void actividad1_3();
void actividad2();
#endif