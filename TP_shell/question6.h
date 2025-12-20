#ifndef QUESTION6_H
#define QUESTION6_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define WELCOME_PROMPT            "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define REGULAR_PROMPT            "ENSEA %% "
#define BUFFER_SIZE               256
#define EMPTY_COMMAND             ""
#define DATE_COMMAND              "date"
#define EXIT_COMMAND              "exit"
#define EXIT_MESSAGE              "Bye bye...\n"
#define PROMPT_EXIT_FORMAT        "ENSEA [exit:%d] %% "
#define PROMPT_SIGNAL_FORMAT      "ENSEA [sign:%d] %% "
#define PROMPT_EXIT_TIME_FORMAT   "ENSEA [exit:%d|%ldms] %% "
#define PROMPT_SIGNAL_TIME_FORMAT "ENSEA [sign:%d|%ldms] %% "
#define MAX_ARGS                  32
#define ARG_SEPARATOR             " "

void display_welcome_prompt(void);
void display_regular_prompt(void);
int execute_command(long int *duration);
void display_prompt_with_status(int status, long int duration_ms);

#endif 