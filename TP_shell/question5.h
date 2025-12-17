#ifndef QUESTION5_H
#define QUESTION5_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define EXIT_COMMAND "exit"
#define EXIT_MESSAGE "Bye bye...\n"
#define PROMPT_EXIT_FORMAT "ENSEA [exit:%d] %% "
#define PROMPT_SIGNAL_FORMAT "ENSEA [sign:%d] %% "

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define NORMAL_PROMPT "ENSEA %% "

#define PROMPT_EXIT_TIME_FORMAT   "ENSEA [exit:%d|%ldms] %% "
#define PROMPT_SIGNAL_TIME_FORMAT "ENSEA [sign:%d|%ldms] %% "

void execut(void);
void display_prompt_with_statusss(int, long, int);


#endif 