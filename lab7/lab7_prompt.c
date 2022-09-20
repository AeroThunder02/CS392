#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include<string.h>
#include<sys/errno.h>


int main()
{

    /*
      TODO:
      1. Use getuid, getpwuid, getcwd to retrieve the username and home 
      directory of the current user
      2. Change the directory to the user's home directory
      3. Print the prompt as specified in homework 5 and wait for user input
    */

    uid_t uID= getuid();
    struct passwd *password;
    password = getpwuid(uID);
    char cwd[256];
    long size;

    
    if(getcwd(cwd, sizeof(cwd)) == NULL){
      printf("getcwd() error");
      return 1;
    }
    else{
      printf("MSh:%s:%s>\n", uID->pw_name, cwd);
    }
    

    /* 
      TODO:
      1. Handle cd commands entered by the user. Check that a single argument 
      is provided. Ignore other commands, but don't exit. Change the current 
      directory according to the user's input.
      2. Handle the exit command. Ensure that it is followed by no arguments.

      ** If tokenizing is giving you trouble, allow the user to omit cd and
      consider the received string as the target directory. There should be 
      no directory named `exit'
    */

    char str[100];
    
    
    return EXIT_SUCCESS;
}