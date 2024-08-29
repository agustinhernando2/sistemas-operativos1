#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/measurement.h"

int main ()
{
    measurement *data;
    int valid_samples;
	
	data = get_instances("./rawdata/datos", &valid_samples);
    if (data == NULL){
        fprintf(stderr, "Error getting instance\n");
        exit(EXIT_FAILURE);
    }

    printf("The binary file contains %d valid_samples of measurements\n", valid_samples);

    int average = get_average(data, valid_samples);
    printf("The average value for validSamples is %d\n", average);
	
	return 0;
}