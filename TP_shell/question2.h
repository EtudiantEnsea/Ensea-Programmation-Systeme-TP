#ifndef QUESTION2_H
#define QUESTION2_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define REGULAR_PROMPT "ENSEA %% "
#define BUFFER_SIZE 256
#define EMPTY_COMMAND ""
#define DATE_COMMAND "date"

void display_welcome_prompt(void);
void display_regular_prompt(void);
void execute_command(void);

#endif