#include "question4.h"

void execute(void)
{
    static int last_status;
    static int has_status = 0;

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    pid_t pid;

    display_prompt_with_status(last_status, has_status);

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);

    if (bytes_read == 0)
    {
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

    buffer[bytes_read - 1] = '\0';

    if (strncmp(buffer, EXIT_COMMAND, strlen(EXIT_COMMAND) + 1) == 0)
    {
        write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
        exit(EXIT_SUCCESS);
    }

    pid = fork();

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
        wait(&last_status);
        has_status = 1;
    }
}

void display_prompt_with_status(int status, int has_status)
{
    char buffer[64];
    int length;

    if (!has_status)
    {
        write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));
        return;
    }

    if (WIFEXITED(status))
    {
        length = snprintf(buffer, sizeof(buffer),
                          PROMPT_EXIT_FORMAT,
                          WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        length = snprintf(buffer, sizeof(buffer),
                          PROMPT_SIGNAL_FORMAT,
                          WTERMSIG(status));
    }
    else
    {
        write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));
        return;
    }

    write(STDOUT_FILENO, buffer, length);
}
