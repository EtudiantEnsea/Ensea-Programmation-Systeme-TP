#include "question7.h"

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
    /* 
     * Reads a command from standard input,
     * handles shell termination (exit / Ctrl+D),
     * and executes the simple command in a child process.
     */

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    int status;
    struct timespec start_time, end_time;
    char *argv[MAX_ARGS] = {0};
    int argc = 0;
    char *token;
    int input_fd = -1;
    int output_fd = -1;

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

    token = strtok(buffer, ARG_SEPARATOR);
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, ARG_SEPARATOR);
    }
    argv[argc] = NULL;

    for(int i = 0; argv[i]!= NULL ; i++){
        if(strcmp(argv[i], "<") == 0){
            input_fd = open(argv[i+1], O_RDONLY);
            argv[i] = NULL;
        }
        if (strcmp(argv[i], ">") == 0){
            output_fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            argv[i] = NULL;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    if (fork() == 0)
    {
        if (input_fd != -1) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != -1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        if (argc == 0){
            execlp(DATE_COMMAND, DATE_COMMAND, NULL);
        }
        else{
            execvp(argv[0], argv);
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