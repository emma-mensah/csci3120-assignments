/**
 * Snippet of main() function from assignment 2 description was adapted and modified in this code
 * Author: Emma Mensah
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

char userInput [MAX_LINE];    //user input
char * args[MAX_LINE/2 + 1];    //holds arguments from user input
char *argsPtr;     //pointer to  arguments
int should_run = 1;
char history_cmds[10][MAX_LINE];
int pid_pos = 0, pid_val,  cmd_pid[10], track = 1;;

void split_commands(){
    int counter = 0;
    argsPtr = strtok(userInput, " ");      /*parsing commands into tokens using space delimiter*/

    while (argsPtr != NULL) {
        args[counter++] = argsPtr;
        argsPtr = strtok(NULL," "); 
    }  
    args[counter] = NULL;   //includes  null to terminate the execution  process
}

void history_func() {
    printf("ID  PID   Command\n");
    
    //loops through command list array displays the commands with their pid from most recent to least recent
    for (int pos = (sizeof(history_cmds)/sizeof(history_cmds[0]))-1; pos >= 0; pos--) {    
        if (cmd_pid[pos] == 0)  {
        } 
        else if (strcmp(history_cmds[pos], "!!") == 0 || strcmp(history_cmds[pos], "history") == 0 ) {
        }
        else {
            printf("%d  %d  %s\n",track, cmd_pid[pos], history_cmds[pos]);
            track++;
        } 
    }     
}

void execute_command() {
    //create new process
    pid_t new_process = fork();
            
    if (new_process == 0) {
        execvp(args[0], args);      //execute  command
        pid_val = new_process;
        cmd_pid[pid_pos]+= pid_val;       //stores pid of command in an array
        exit(1);
                
    }else if (new_process > 0) {
        wait(NULL); 
        pid_val = new_process;
        cmd_pid[pid_pos]+= pid_val;
    }
    else{
        printf("ERROR");
        exit(0);
    }
}

int main( void) {
    while (should_run) {
        printf("CSCI3120>");            //prints shell prompt
        fflush(stdout);
   
        fgets(userInput, MAX_LINE, stdin);

        if ((userInput[strlen (userInput) - 1] == '\n') && (strlen(userInput) > 0)){
            userInput[strlen (userInput) - 1] = '\0';
        }

        strcpy(history_cmds[pid_pos],userInput);      //store user commands in history array
        	
        if (strcmp(userInput,"exit")==0) {          //checks if user inputs an exit command, if yes, terminate program
            should_run = 0;
        }
        
        if(strcmp(userInput,"!!") == 0) {
            for (int pos = (sizeof(history_cmds)/sizeof(history_cmds[0]))-1; pos >= 0; pos--) {    
                if (cmd_pid[pos] == 0)  {
                } 
                else if (strcmp(history_cmds[pos], "!!") == 0 || strcmp(history_cmds[pos], "history") == 0 ) {
                }
                else {
                    printf("%s\n",history_cmds[pos]);

                    //creates new process for most recent command and executes it
                    pid_t new_process = fork();
            
                    if (new_process == 0) {
                        execvp(history_cmds[pos], args);      //execute  command
                        exit(1);
                                
                    }else if (new_process > 0) {
                        wait(NULL); 
                    }
                    else{
                        printf("ERROR");
                        exit(0);
                    }
                    break;
                } 
            }    
        }

        if (strcmp(userInput, "history") == 0)      //checks if user input a history command, if yes, display the history
            {
                history_func();
        }

        split_commands();       //calls the function to parse user input
        execute_command();      //calls the function to execute commands
        
        pid_pos++;
    }
    return 0;
}


