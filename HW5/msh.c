#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include "msh.h"

volatile sig_atomic_t catch = 0;
void handler(int sig){
    catch = 1;
    printf("\nCannot exit terminal with ^C!\n");
};
 

int main() {
    //Register signal handler
    struct sigaction sa;
    sa.sa_handler = handler;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
    }

    //We need to do this initially so that we may get the username for our minishell
    uid_t uID;
    struct passwd *pwd;
    if ((pwd = getpwuid(uID = getuid())) == NULL){
        printf("Error: Cannot get passwd entry. %s.\n", strerror(errno));
    }

    char input[1024];

    while (1) {
        catch = 0;
        //Get cwd so that we may display it in our minishell
        char* cwd = getcwd(NULL, 0);
        if (cwd == NULL) {
            printf("Error: Cannot get current working directory. %s.\n", strerror(errno));
            continue;
        }

        if(catch == 1){
            continue;
        }
        
        //Use the username and cwd aquired to print format
        printf("MSh:%s:%s>", pwd->pw_name, cwd);
       
        //take user input
        fgets(input, 1024, stdin);
            
        //This code will remove the newline character at the end of a users input, that way we never have to worry about it when checking input
        int n = 0;
        while(input[n] != '\0'){
            n++;
        }
        if (n == 1) continue;
        input[n-1] = '\0';

        //if the user types exit, then exit
        if(strcmp(input, "exit") == 0) {
            break;
        }

        // count spaces in string, we need to include the null
        int spaces = 2;
        for (int i = 0; i <= input[i]; i++){
            if (input[i] == ' ') spaces++;
        }
        
        //malloc space to store the arguments, that way we can check the number of arguments easier for cd
        char** arguments = malloc(1024 * spaces);
        if (arguments == NULL) {
            printf("Error: malloc() failed. %s.\n", strerror(errno));
        }
        
        //This just initializes the space we allocated. I had to do this because otherwise strtok would give garbage in some areas
        char* trash = '\0';
        for (int i = 0; i < spaces; i++){
            arguments[i] = trash;
        }

        //Here we tokenize the string and put it into our array
        arguments[0] = strtok(input, " ");
        for (int i = 1; i < spaces - 1; i++){
            arguments[i] = strtok(NULL, " ");
        }
        arguments[spaces] = NULL; //remember to make the last element NULL
        
        //In the instance exit recieves an argument, we need to check for it
        if (strcmp(arguments[0], "exit") == 0){
            //If it did, print out a warning/error and keep the shell running.
            if(arguments[1] != NULL){
                printf("Warning: command 'exit' does not take arguments.\n");
                continue;
            }
        }

        //check for cd
        else if (strcmp(arguments[0], "cd") == 0) {
            
            //first check if there are too many arguments, if so, error.
            if (arguments[2] != NULL) {
                printf("Error: Too many arguments to cd. %s.\n", strerror(errno));
            } 
            //next we have to check if cd recieved no arguments or '~'
            else if (arguments[1] == NULL || strcmp(arguments[1], "~") == 0) {
                
                //If so, get the password so we can change to the home directory
                struct passwd *pwd = getpwuid(getuid());
                if (pwd == NULL) {
                    printf("Error: Cannot get passwd entry. %s.\n", strerror(errno));
                } 
                else {
                    char *homedir = pwd->pw_dir;
                    if (chdir(homedir) == -1) {
                        printf("Error: Cannot change directory to '%s'. %s.\n", homedir, strerror(errno));
                    }
                }
            } 
            //The last case is that cd recieved an argument, so we check if we can chdir to it
            else {
                if (chdir(arguments[1]) == -1) {
                    printf("Error: Cannot change directory to '%s'. %s.\n", arguments[1], strerror(errno));
                }
            }
            //we finished parsing this command, so free args and go to next iteration
            free(arguments); 
            continue;
        }

        //This is for exec. since commands are stored in /bin/ we need to include it in our call
        char* binary = (char*)malloc(1024);
        if (binary == NULL) {
            ("Error: malloc() failed. %s.\n", strerror(errno));
        }
        strcpy(binary, "/bin/");
        strcat(binary, arguments[0]);
        
        //Check if the command run is an executable. If not, it exists in bin.
        if ((arguments[0])[0] != '.') {
            arguments[0] = binary;
        }

        int pid;
        //fork the process
        if ((pid = fork()) == -1) {
            printf("Error: fork() failed. %s.\n", strerror(errno));
        }

        //Exec the command
        if (pid == 0) {
            int exc = execvp(arguments[0], arguments);
            if (exc == -1) {
                printf("Error: exec() failed. %s.\n", strerror(errno));
                free(binary);
                free(arguments);
                exit(0);
            }
            
        } 
        else {
            //Reap the child process
            if (wait(NULL) == -1) {
                printf("Error: wait() failed. %s.\n", strerror(errno));
            }
            
        }

        //free malloc'd variables
        free(binary);
        free(arguments);
    }
}
