#include "question5.h"

void execut(void)
{
    static int last_status;
    static long last_time_ms;
    static int has_status = 0;

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    pid_t pid;
    struct timespec start, end;

    display_prompt_with_statusss(last_status, last_time_ms, has_status);

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);

    /* Ctrl-D */
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

    clock_gettime(CLOCK_MONOTONIC, &start);

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
        clock_gettime(CLOCK_MONOTONIC, &end);

        last_time_ms =
            (end.tv_sec - start.tv_sec) * 1000 +
            (end.tv_nsec - start.tv_nsec) / 1000000;

        has_status = 1;
    }
}


void display_prompt_with_statusss(int status, long time_ms, int has_status)
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
                          PROMPT_EXIT_TIME_FORMAT,
                          WEXITSTATUS(status), time_ms);
    }
    else if (WIFSIGNALED(status))
    {
        length = snprintf(buffer, sizeof(buffer),
                          PROMPT_SIGNAL_TIME_FORMAT,
                          WTERMSIG(status), time_ms);
    }
    else
    {
        write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));
        return;
    }

    write(STDOUT_FILENO, buffer, length);
}
