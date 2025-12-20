#include "question6.h"

void display_prompt_with_status(int status, long duration_ms){
    char prompt[BUFFER_SIZE];
    int prompt_length;

    if(WIFEXITED(status)){
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_EXIT_TIME_FORMAT, WEXITSTATUS(status), duration_ms);
    }
    else if (WIFSIGNALED(status)) {
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_SIGNAL_TIME_FORMAT, WTERMSIG(status), duration_ms);
    } 
    else {
        prompt_length = snprintf(prompt, BUFFER_SIZE, REGULAR_PROMPT);
    }

    write(STDOUT_FILENO, prompt, prompt_length);
}


int execute_command(long int *duration_ms){
    
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    int status;
    struct timespec start_time, end_time;
    char *argv[MAX_ARGS] = {0};    //We will add this to point towards an array where we will put our commands to be executed.
    int argc = 0;
    char *token;

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
        /*We will add the following code, below this comment, in order to separate what we filled in the buffer into different commands within the same command, so we can use arguments,
        and store them into the argv which is a vector, as an example we have the "fortune -s", that will go search for short fortune sayings.*/
    token = strtok(buffer, ARG_SEPARATOR);    //We will add 
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, ARG_SEPARATOR);
    }
    argv[argc] = NULL;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    if (fork() == 0)
    {
        if (argc == 0){
            execlp(DATE_COMMAND, DATE_COMMAND, NULL);
        }
        else{
            execvp(argv[0], argv); //Here we will change the execlp to execvp to execute a bunch of vector stored in the argv.
        }

        exit(EXIT_FAILURE);
    }
    
    wait(&status);
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    *duration_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

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
    long int duration_ms = 0;
    
    display_welcome_prompt();
    display_regular_prompt();

    while(1){
        status = execute_command(&duration_ms);
        display_prompt_with_status(status, duration_ms);
    }

    return EXIT_SUCCESS;
}
