#include "question4.h"

void display_prompt_with_status(int status){
    char prompt[BUFFER_SIZE];
    int prompt_length;

    if(WIFEXITED(status)){
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_EXIT_FORMAT, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_SIGNAL_FORMAT, WTERMSIG(status));
    } 
    else {
        prompt_length = snprintf(prompt, BUFFER_SIZE, REGULAR_PROMPT);
    }

    write(STDOUT_FILENO, prompt, prompt_length);
}


int execute_command(){
    /* 
     * Reads a command from standard input,
     * handles shell termination (exit / Ctrl+D),
     * and executes the simple command in a child process.
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
    return status;
}

void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
    write(STDOUT_FILENO, REGULAR_PROMPT, strlen(REGULAR_PROMPT));
}

int main(){

    int status = 0;
    
    display_welcome_prompt();
    display_regular_prompt();

    while(1){
        status = execute_command();
        display_prompt_with_status(status);
    }

    return EXIT_SUCCESS;
}