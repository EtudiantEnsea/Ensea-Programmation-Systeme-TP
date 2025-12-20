#include "question1.h"

/*
In this first question, we will have to display a welcoming prompt :"Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n" that we can find in the file question1.h and that is defined as WELCOME_PROMPT,
we will also have to display a welcoming prompt :"ENSEA %% " that is defined as NORMAL_PROMT and that we can also find in the file question1.h, 
for that we will use the command "write(int fd, const void *buf, size_t count)";
    */
void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}
/*
To use this command properly we will have to put STDOUT_FILENO as the first argument to display on the screen, for the second argument, we fill it with our welcoming prompt,
the third argument is necessary to define how much of the second argument do you want to display, for our case we will show the full welcoming prompt with the command strlen() that gives the length of its argument.
    */
void display_regular_prompt(){
    write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));
}
/*
We will do the same thing that we did above, except it's for the normal prompt.
    */

int main(void){

    display_welcome_prompt();
    display_regular_prompt();
    
    return EXIT_SUCCESS;
}
