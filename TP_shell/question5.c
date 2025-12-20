#include "question5.h"

void display_prompt_with_status(int status, long duration_ms){
    char prompt[BUFFER_SIZE];
    int prompt_length;

    if(WIFEXITED(status)){
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_EXIT_TIME_FORMAT, WEXITSTATUS(status), duration_ms);    //We change the prompt format to include the writing of the time consumed to execute a command.
    }
    else if (WIFSIGNALED(status)) {
        prompt_length = snprintf(prompt, BUFFER_SIZE, PROMPT_SIGNAL_TIME_FORMAT, WTERMSIG(status), duration_ms);    //We change the format here too.
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
    struct timespec start_time, end_time;     /*We declare 2 new time variables, each variable will have seconds sub-variable and nanoseconds sub-variable. 
                                                We can do that thanks to the time library we  included in question5.h .*/

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

    clock_gettime(CLOCK_MONOTONIC, &start_time);    //We start our countdown after we type a command and we press enter.

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
    clock_gettime(CLOCK_MONOTONIC, &end_time);    //We end our countdown just after the execution of our command.

    *duration_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000;    //Here is the formula to calculate the time of the execution of our command.

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
