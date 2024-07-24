#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/functions.h"

int main (int argc, char *argv[])
{

    if(argc == 1){
        while(get_running()){
            show_prompt();
            get_command();
            exec_command();  
        }
    }

    return EXIT_SUCCESS;
}
