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

char command[500];
char pwd[256];
int running = 1;
char *token;
char *const *argumentos;

void extern_command(char *c[]);
void echo_shell();
void clear_shell();
void exit_shell();
void exchange_directory(char *dir);
char* get_directory();
void show_prompt();
void get_command();
char** get_arguments_for_extern_command();


/**
* @brief actualiza las variables de entorno cuando se cambia de directorio
* y personaliza el command prompt de myshell
**/
void show_prompt(){
    char* username = getenv(USER);
	char hostname[20];
    gethostname(hostname, sizeof(hostname));
    if(getcwd(pwd,sizeof(pwd)) == NULL){
    	perror("Error");
    }
    setenv(PWD,pwd,1);
    // ansi colors https://talyian.github.io/ansicolors/
    printf(AMARILLO"%s@",username);
    printf(GRIS"%s:~%s$",hostname,pwd);
    printf(CELESTE" ");

}

/**
* @brief compara el comando y ejecuta funciones que respondan en funcion de él.
**/
void commandEjecute(){

    if((strncmp(command,"clr",3) == 0)||(strncmp(command,"clear",4) == 0)){
		clear_shell();
	}else if((strncmp(command,"quit",4) == 0)||(strncmp(command,"exit",4) == 0)){
		exit_shell();
	}else if((strncmp(command,"cd ",3) == 0)){ 
		exchange_directory(get_directory());
	}else if((strncmp(command,"echo",4) == 0)){
		echo_shell();
	}else{
		extern_command(get_arguments_for_extern_command());
	}

}

/**
* @brief Limpia el command line de myshell.
**/
void clear_shell(){
    printf("\033[H\033[J");
}

/**
* @brief exit.
**/
void exit_shell(){
    running = 0;
}

/**
* @brief solicita el directorio actual.
* @return currentDirectory
**/
char* get_directory(){
	token = strtok(command,SPACE);
	if(token != NULL){
			token = strtok(NULL,"\n");
	}
	char *arg= malloc(500*sizeof(char));
 	if(strcmp(token,"-") == 0){
  	return token;
  }
  if(strstr(getenv(PWD),token)!=NULL){ 
  	strcat(arg,"/");
		strcat(arg,token);
  }else{
  	strcat(arg,getenv(PWD));
  	strcat(arg,"/");
		strcat(arg,token);
  }
	return arg;
}

/**
* @brief modifica el directorio actual en la variable de entorno.
**/
void exchange_directory(char *dir){
	if(strcmp(dir,"-") == 0){
		dir = getenv(OLDPWD);
	}
	setenv(OLDPWD,pwd,1);
	if(chdir(dir)!=0){
		perror(ROJO"Error");
	}	
	else{
		setenv(PWD, getcwd(pwd, 256), 1);
	}
}

/**
* @brief ejecuta echo.
**/
void echo_shell(){
    token = strtok(command,SPACE);
	if(token != NULL){ 
			token = strtok(NULL,"\n");
	}
	if(strncmp(token,DOLLAR,1) == 0){
		char *env = getenv(token+1);
		if(env != NULL) printf("%s\n",env);
		else {
			fprintf(stderr,ROJO"Error: Environment variable not found");
			printf("\n");
			}

	}else {
		if(token[0]=='"' && (token[strlen(token)]='"')){
			char comentario[strlen(token)-2];
			for(int i=0; i< strlen(token)-2;i++){ 
				comentario[i]=token[i+1];
			}
            comentario[strlen(token)-3]='\0';
			printf("comentario:%ld, %ld   %s\n",strlen(token),strlen(comentario),comentario);
		}
		else printf("%s\n",token);
	}
}

/**
* @brief solicitar un comando ingresado por el usuario el cual se guardará en una variable command.
**/
void get_command(){
	fgets(command,sizeof(command),stdin); //escanea el command ingresado
}

char** get_arguments_for_extern_command(){
	char **arg= malloc(50*sizeof(char*));
	int index=0;

	token = strtok(command,"\n");
	arg[index] =  strdup(token);
	token = strtok(arg[index]," ");
	if(token != NULL){
		arg[index] =  strdup(token);
	}else{
		arg[index+1] = NULL;
		return arg;
	}
	index++;
	while (token && (token = strtok(NULL, " "))) {
		arg[index] = strdup(token);
		index++;
	}
	arg[index] = NULL;
	return arg;
}
/**
* @brief ejecuta el comando en caso con system como ultima alternativa.
**/
void extern_command(char *c[]){
    pid_t pid = fork();
	switch (pid)
	{
	case -1:
		perror(ROJO"fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		argumentos=c;
		char *path= malloc(100*sizeof(char));
		strcat(path,"/bin/");
		strcat(path,argumentos[0]);
		if(execv(path,argumentos)==-1){
    		perror(ROJO"Error");
    	}
		exit(EXIT_SUCCESS);
		break;
	default:
		wait(0);
		break;
	}
}
