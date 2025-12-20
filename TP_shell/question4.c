#include "question4.h"

void display_prompt_with_status(int status){
    char prompt[BUFFER_SIZE];
    int prompt_length;

    if(WIFEXITED(status)){    //If our child process ended in a natural way, we print this message.
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_EXIT_FORMAT, WEXITSTATUS(status));    //We change the prompt format to include the type of death of the child process.
    }
    else if (WIFSIGNALED(status)) {    //If our child process ended in a non natural way, or got murdered, we print this message.
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_SIGNAL_FORMAT, WTERMSIG(status));    //We change the prompt here too.
    } 
    else {
        prompt_length = snprintf(prompt, BUFFER_SIZE, REGULAR_PROMPT);
    }

    write(STDOUT_FILENO, prompt, prompt_length);
}


int execute_command(){

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    int status;    //The status variable is used to store the way our child process was ended, whether it was executed (natural way) or it was killed (unnatural way)

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
