#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char *argv[]) {

    /*
      TODO:
      Use fork() and pipe(), but NOT popen().

      Create a pipe through which a child process will send two integers to 
      the parent. The parent will add the integers and print the result to 
      the terminal. 
    */
    int pid;
    int fd[2];
    pipe(fd);

    //Fork and create a pipe between parent and child.
    if ((pid = fork()) == -1){
      printf("Error: fork failed. %s\n", strerror(errno));
      return EXIT_FAILURE;
    }

    if (pid == 0){
      //close input
      close(fd[0]);
      int a = 10;
      int b = 3;
      //child writes the data of a and b to the pipe output
      write(fd[1], &a, sizeof(int));
      write(fd[1], &b, sizeof(int));
     
      
    }
    else{
      //close output
      close(fd[1]);
      int arecieve = 0;
      int brecieve = 0;
      //read information in from the output side of the pipe
      read(fd[0], &arecieve, sizeof(int));
      read(fd[0], &brecieve, sizeof(int));
      int result = arecieve+brecieve;
      printf("the sum of the two ints is %d\n", result);
      
    }
    /*
      OPTIONAL:
      Make a second child, which will do the addition. In this case, the parent
      waits for the children to terminate. (See Lab 6 or 7.)
    */
    if ((pid = fork() == -1)){
      printf("Error: fork failed. %s\n", strerror(errno));
      return EXIT_FAILURE;
    }

    
    else if (pid == 0){
  
      int pid;
      int fd[2];
      pipe(fd);

      //Fork and create a pipe between parent and child.
      if ((pid = fork()) == -1){
        printf("Error: fork failed. %s\n", strerror(errno));
        return EXIT_FAILURE;
      }

      if (pid == 0){
        //close input
        close(fd[0]);
        int a = 10;
        int b = 3;
        //child writes the data of a and b to the pipe output
        write(fd[1], &a, sizeof(int));
        write(fd[1], &b, sizeof(int));
      
        
      }
      else{
        //close output
        close(fd[1]);
        int arecieve = 0;
        int brecieve = 0;
        //read information in from the output side of the pipe
        read(fd[0], &arecieve, sizeof(int));
        read(fd[0], &brecieve, sizeof(int));
        int result = arecieve+brecieve;
        printf("the sum of the two ints is %d\n", result);
        
      }
    }

    else{
      //Parent only has to wait for its child to finish.
      waitpid(pid, NULL, 0);
    }
    return EXIT_SUCCESS;
}
