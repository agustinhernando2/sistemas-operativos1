#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include <stdbool.h>

typedef struct __attribute__((__packed__))
{
    unsigned short int version;         // 2 bytes
    unsigned short int drxVersion;      // 2 bytes
    char r1[4];                         // 4 bytes
    double initCW;                      // 8 bytes
    float azimuth;                      // 4 bytes
    float elevation;                    // 4 bytes
    unsigned short int idVolumen;       // 2 bytes
    unsigned short int idBarrido;       // 2 bytes
    unsigned short int idConjunto;      // 2 bytes
    unsigned short int idGrupo;         // 2 bytes
    unsigned short int idPulso;         // 2 bytes
    bool iniBarrido;                    // 1 bytes
    bool finBarrido;                    // 1 bytes
    bool finGrupo;                      // 1 bytes
    bool inhibido;                      // 1 bytes
    unsigned short int validSamples;    // 2 bytes
    unsigned short int nroAdquisicion;  // 2 bytes
    char r2[2];                         // 2 bytes
    unsigned int nroSecuencia;          // 4 bytes
    unsigned long int readTime_high;    // 8 bytes    
    unsigned long int readTime_low;     // 8 bytes    
    char r3[64];                        // 64 bytes
} measurement;

/**
 * @brief        Return the instances of the measurement structure
 * @param[in]    path        Path to the file
 * @param[out]   instances   Number of instances
 * @return       measurement  Pointer to the first instance
 */
measurement *get_instances(char* path, int* instances);

/** @brief        Return the average of the field valid samples of
 * @param[in]    measurement        Pointer to the first instance
 * @param[in]    instances          Number of instances
 * @return       average            Average of valid samples
 */
int get_average(measurement* measurements, int instances);

#endif