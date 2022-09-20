#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
    
    int ret[2];
    int c1_c2[2]; //Child 1 -> child 2
    int c2_p[2]; //Child 2 -> parent

    if (argc != 2){
        printf("Usage: ./pipes <directory>");
    }

    //Since ls -l will runs in the current working directory by default, we can begin by switching to the targe directory
    if (chdir(argv[1]) != 0){
        printf("Error: No such directory.\n");
        return EXIT_FAILURE;
    }

    //Creation of ls and grep commands to use in execv later
    char *ls[3];
    ls[0] = "/bin/ls";
    ls[1] = "-l";
    ls[2] = NULL;

    char *grep[3];
    grep[0] = "/bin/grep";
    grep[1] = "^d";
    grep[2] = NULL;

    //Pipe creation
    pipe(c1_c2);
    pipe(c2_p);

    //Fork
    if ((ret[0] = fork()) == 0) {
        // Child 1
        close(c1_c2[READ_END]); //close read end
        dup2(c1_c2[WRITE_END], 1); //Open the write end, since we are writing the output of ls
        close(c2_p[WRITE_END]); //close read and write and of pipe we are not using
        close(c2_p[READ_END]);
        
        //Exec ls -l
        if(execv(ls[0], ls) == -1){
            printf("Error: exec failed. %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        exit(0);
    }
    else if (ret[0] == -1){
        printf("Error: fork failed. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    //Fork
    if ((ret[1] = fork()) == 0) {
        // Child 2 
        close(c1_c2[WRITE_END]); //close write end of pipe
        dup2(c1_c2[READ_END], 0); //Open read end, since we want to read the output of ls -l
        close(c2_p[READ_END]); //Dont need read end of this pipe
        dup2(c2_p[WRITE_END], 1); //Open write end, since we want to write the output of grep

        //Exec grep ^d
        if(execv(grep[0], grep) == -1){
            printf("Error: exec failed. %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        exit(0);
    }
    else if (ret[1] == -1){
        printf("Error: fork failed. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    close(c2_p[WRITE_END]); //close up remaining pipes
    close(c1_c2[WRITE_END]);
    close(c1_c2[READ_END]);

    char c = 0;
    int lines = 0;
    while(read(c2_p[READ_END], &c, 1) != 0 ) { //print out the output character by character, increment line count when we reach a \n
        if(c == '\n'){
            lines++;
        }
        printf("%c", c);
        
    }
    printf("Lines: %d\n", lines);
    

    while(wait(NULL) > 0); //reap children
    
    return EXIT_SUCCESS;
}