#include "question3.h"

void execute_command(){
    /* 
     * Reads a command from standard input,
     * handles shell termination (exit / Ctrl+D),
     * and executes the command in a child process.
     */

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    int status;

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

    if(bytes_read == 0){
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

    buffer[bytes_read - 1] = '\0';

    if(strcmp(buffer, EXIT_COMMAND) == 0){
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

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