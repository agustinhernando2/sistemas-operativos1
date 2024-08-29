#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/measurement.h"

measurement* get_instances(char *path, int *instances){

    int fd;
    size_t size;
    struct stat attributes;

    fd = open(path, O_RDONLY);
    if (fd < 0){
        fprintf(stderr, "Opening file failed\n");
        return NULL;
    }

    // get attributes of the file and save them in s    
    if(fstat(fd, &attributes) < 0){
        fprintf(stderr, "Obtaining stats of the file failed\n");
        close(fd);
        return NULL;
    }
        
    size = attributes.st_size;

    // calculate the number of structures
    *instances = size / sizeof(measurement);

    // map the file into memory
    // params: address, size, protection, flags, file descriptor, offset
    // NULL means that the kernel chooses the address
    // PROT_READ means that the memory is read only
    // MAP_SHARED means that the changes are shared with the file
	measurement *data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    
    if(data == MAP_FAILED){
        fprintf(stderr,"Mapping data Failed\n");
        close (fd);
        return NULL;
    }

    close(fd);
    
    return data;
}

int get_average(measurement *data, int instances){

    int average = 0;
    for(int i=0; i<instances; i++){
        average += data[i].validSamples;
    }
    return average / instances;
}