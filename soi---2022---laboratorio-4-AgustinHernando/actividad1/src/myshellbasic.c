#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "functions.c"
int main (int argc, char *argv[])
{

    if(argc == 1){
        while(running){
            show_prompt();
            get_command();
            commandEjecute();  
        }
    }

    return EXIT_SUCCESS;
}
