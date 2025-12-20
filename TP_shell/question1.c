#include "question1.h"

void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
    write(STDOUT_FILENO, NORMAL_PROMPT, strlen(NORMAL_PROMPT));
}

int main(void){

    display_welcome_prompt();
    display_regular_prompt();
    
    return EXIT_SUCCESS;
}