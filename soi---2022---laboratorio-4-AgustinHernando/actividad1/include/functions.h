// include/functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

#define AMARILLO "\x1b[33m"
#define GRIS "\x1b[37m"
#define CELESTE "\x1b[36m"
#define ROJO     "\x1b[31m"

#define DOLLAR "$"
#define SPACE " "
#define PWD "PWD"
#define USER "USER"
#define OLDPWD "OLDPWD"


extern char command[500];
extern char pwd[256];
extern int running;
extern char *token;
extern char *const *argumentos;

/**
 * @brief obtiene el valor de la variable running.
 * @return running
 * */
int get_running();

/**
* @brief actualiza las variables de entorno cuando se cambia de directorio
* y personaliza el command prompt de myshell
**/
void show_prompt();

/**
* @brief compara el comando y ejecuta funciones que respondan en funcion de él.
**/
void exec_command();

/**
* @brief Limpia el command line de myshell.
**/
void clear_shell();

/**
* @brief exit.
**/
void exit_shell();

/**
* @brief solicita el directorio actual.
* @return currentDirectory
**/
char* get_directory();

/**
* @brief modifica el directorio actual en la variable de entorno.
**/
void exchange_directory(char *dir);

/**
* @brief ejecuta echo.
**/
void echo_shell();

/**
* @brief solicitar un comando ingresado por el usuario el cual se guardará en una variable command.
**/
void get_command();

/**
 * @brief obtiene los argumentos para el comando externo.
 * @return argumentos
 * */
char** get_arguments_for_extern_command();

/**
* @brief ejecuta el comando en caso con system como ultima alternativa.
**/
void extern_command(char *c[]);

#endif // FUNCTIONS_H