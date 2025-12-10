#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define NORMAL_PROMPT "ENSEA %% "
#define MAX_LINE_SIZE 256


void display_welcome_prompt(void);
void display_regualar_prompt(void);
void execute_one_simple_command(void);


int main() {

    display_welcome_prompt();
    while(1){
        display_regualar_prompt();
        execute_one_simple_command();

    }


    return EXIT_SUCCESS;
}

void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regualar_prompt(){
    int status = write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));

    if (status == -1){
        exit(EXIT_FAILURE);
    }
}


void execute_one_simple_command(){
    char buffer_command_line[MAX_LINE_SIZE]={0};

    int nb_char_read = read(STDIN_FILENO, buffer_command_line, MAX_LINE_SIZE);
    buffer_command_line[nb_char_read -1]=0;


    if(fork()==0){
        execlp(buffer_command_line, buffer_command_line, NULL);
        exit(EXIT_FAILURE);
    }
    int status;
    wait(&status);

    if (strcmp(buffer_command_line, "exit") == 0){
        printf("Bye Bye...");

    }
}
