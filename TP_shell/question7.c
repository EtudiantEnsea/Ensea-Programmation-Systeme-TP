#include "question7.h"

void display_prompt_with_status(int status, long duration_ms){
    /*
     * Displays the shell prompt including:
     *  - the exit status or signal of the previous command
     *  - the execution time in milliseconds
     */
    
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
     * Reads a command from standard input, parses arguments,
     * handles input/output redirections,
     * executes the command in a child process,
     * and measures its execution time.
     *
     * The shell terminates on "exit" command or Ctrl+D.
     */

    char buffer[BUFFER_SIZE] = {0};
    char *argv[MAX_ARGS] = {0};
    char *token;

    int bytes_read;
    int status;
    int argc = 0;
    int input_fd = ERROR_REDIRECTION;
    int output_fd = ERROR_REDIRECTION;

    struct timespec start_time, end_time;
    
    /* Read user input from standard input */
    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    
    /* Ctrl+D: end of input, exit the shell cleanly */
    if(bytes_read == 0){
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

    buffer[bytes_read - 1] = '\0';

    /* Built-in command: exit the shell */
    if(strcmp(buffer, EXIT_COMMAND) == 0){
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

    /* Split command line into arguments for execvp */
    token = strtok(buffer, ARG_SEPARATOR);
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, ARG_SEPARATOR);
    }
    argv[argc] = NULL;

    /* Detect input/output redirections (< and >) */
    for(int i = 0; argv[i]!= NULL ; i++){
        if(strcmp(argv[i], "<") == 0){
            input_fd = open(argv[i+1], O_RDONLY);
            argv[i] = NULL;
            break;
        }
        if (strcmp(argv[i], ">") == 0){
            output_fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            argv[i] = NULL;
            break;
        }
    }

    /* Start measuring execution time */
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    /* Child process: apply redirections if any */
    if (fork() == 0)
    {
        if (input_fd != ERROR_REDIRECTION) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != ERROR_REDIRECTION) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        /* Execute command */
        if (argc == 0){
            execlp(DATE_COMMAND, DATE_COMMAND, NULL);
        }
        else{
            execvp(argv[0], argv);
        }

        exit(EXIT_FAILURE);
    }
    
    wait(&status);
    /* Stop measuring execution time */
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    /* Compute execution duration in milliseconds */
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
    /*
     * Main REPL loop:
     * display prompt, execute command, then display status
     */

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
