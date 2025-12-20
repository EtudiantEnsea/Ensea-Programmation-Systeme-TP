#include "question2.h"

void execute_command(){

    char buffer[BUFFER_SIZE] = {0}; // We initialise the buffer that has a size of 256 defined in question2.h, with 0
    int bytes_read; //We initialse also the variable used in the read command to calculate the size of characters written in our buffer
    int status;

    bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE); /*The read command's first argument takes whatever we type on the keyboard as an input and store it in the second argument, 
                                                            the third argument is used to limit how much we write in the buffer to prevent buffer overflow. */
    
    buffer[bytes_read - 1] = '\0';//Whatever we put in the buffer in reality adds a "\n" after the last letter written and since buffer's starting index is 0 and bytes_read's starting index is 1 we code it like this

    if (fork() == 0) //We put an if statement to execute the command through the child process.
    {
        if (strcmp(buffer, EMPTY_COMMAND) == 0){    //We added that if we right nothing and press enter the shell will give us the date.
            execlp(DATE_COMMAND, DATE_COMMAND, NULL);
        }
        else{
            execlp(buffer, buffer, NULL);
        }

        exit(EXIT_FAILURE);
    }

    wait(&status);
}

void display_welcome_prompt(void){
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
    write(STDOUT_FILENO, REGULAR_PROMPT, strlen(REGULAR_PROMPT));
}

int main(){
    
    display_welcome_prompt();

    while(1){  //Always display the normal prompt even after executing some commands like date or fortune.
        display_regular_prompt();
        execute_command();
    }

    return EXIT_SUCCESS;
}
