#ifndef QUESTION4_H
#define QUESTION4_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define EXIT_COMMAND "exit"
#define EXIT_MESSAGE "Bye bye...\n"
#define PROMPT_EXIT_FORMAT "ENSEA [exit:%d] %% "
#define PROMPT_SIGNAL_FORMAT "ENSEA [sign:%d] %% "

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define NORMAL_PROMPT "ENSEA %% "

void execute(void);
void display_prompt_with_status(int, int);

#endif 