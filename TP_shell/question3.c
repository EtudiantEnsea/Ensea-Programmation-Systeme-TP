#include "question3.h"

void execute_(){

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);

        buffer[bytes_read - 1] = '\0';


        if (strncmp(buffer, EXIT_COMMAND, strlen(EXIT_COMMAND) + 1) == 0)
        {
            write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
            exit(EXIT_SUCCESS);
        }

        if(strcmp(buffer, "exit") == 0){
            exit(EXIT_FAILURE);
        }


        pid_t pid = fork();

        if (pid == 0)
        {
            if (strcmp(buffer, "") == 0){
                execlp("date", "date", NULL);
            }
            else{
            execlp(buffer, buffer, NULL);
            }

            _exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
}