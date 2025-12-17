#ifndef QUESTION1_H
#define QUESTION1_H

#include <unistd.h>
#include <string.h>

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define NORMAL_PROMPT "ENSEA %% "


void display_welcome_prompt(void);
void display_regular_prompt(void);

#endif