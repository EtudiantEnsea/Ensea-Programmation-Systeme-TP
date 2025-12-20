#include "question2.h"

void execute_command(){

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    int status;

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    buffer[bytes_read - 1] = '\0';

    if (fork() == 0)
    {
        if (strcmp(buffer, EMPTY_COMMAND) == 0){
            execlp(DATE_COMMAND, DATE_COMMAND, NULL);
        }
        else{
            execlp(buffer, buffer, NULL);
        }

        exit(EXIT_FAILURE);
    }

    wait(&status);
}

void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
    write(STDOUT_FILENO, REGULAR_PROMPT, strlen(REGULAR_PROMPT));
}

int main(){
    
    display_welcome_prompt();

    while(1){
        display_regular_prompt();
        execute_command();
    }

    return EXIT_SUCCESS;
}