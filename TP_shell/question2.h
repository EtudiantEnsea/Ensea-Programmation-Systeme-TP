#ifndef QUESTION2_H
#define QUESTION2_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void execute_command(void);

////////////////////////////////////
#define EXIT_COMMAND "exit"
#define EXIT_MESSAGE "Bye bye...\n"
//////////////////////////////////:/


/////////////////////////////////////////////////////
#define NORMAL_PROMPT "ENSEA %% "
#define PROMPT_EXIT_FORMAT "ENSEA [exit:%d] %% "
#define PROMPT_SIGNAL_FORMAT "ENSEA [sign:%d] %% "
/////////////////////////////////////////////////////
 
#endif