#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


void usage(){
    printf("Usage: ./maxfile <directory>\n");
}

//Largestfile will take a directory and 5 storage variables as input and find the largest user writable and user non-writeable files.
//It will also keep track of the total disk usage
//It will then update the storage variables with the sizes and names of the files
void Largestfile(char *dir_input, long int *LargestWsize, long int *LargestNWsize, char *LargestWfile, char *LargestNWfile, long int *diskUsage){
    
    char dirname[1000]; //We will have to keep track of the current directory name  to make sure we read the files correctly
    DIR *dir;
    struct dirent *dp;
    struct stat statbuf;

    if ((dir = opendir(dir_input)) == NULL) {
        fprintf(stderr, "Error: Cannot open directory: %s\n", dir_input);
        exit(1);
    }

    while((dp = readdir(dir)) != NULL){
        //check to make sure the directory isnt . or ..
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){
            continue;
        }
        
        strcpy(dirname, dir_input);
        strcat(dirname, "/");
        strcat(dirname, dp->d_name);
        
        //use stat to get entry info
        if (stat(dirname, &statbuf) < -1){
            fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", dirname, strerror(errno));
            continue;
        }

        //Every file/directory we look at takes up disk space, so we must update it each loop iteration
        *diskUsage += statbuf.st_size;

        //If its a regular file, then we check permissions
        if(S_ISREG(statbuf.st_mode)){
            //If user writable
            if ((statbuf.st_mode & S_IWUSR) > 0){

                //If we found a file with a larger size, update variables
                if (statbuf.st_size > *LargestWsize){ 
                    *LargestWsize = statbuf.st_size;
                    strcpy(LargestWfile, dp->d_name);
                }
            }

            //If not user writable
            else{

                //If we found a file with a larger size, update variables
                if (statbuf.st_size > *LargestNWsize){ 
                    *LargestNWsize = statbuf.st_size;
                    strcpy(LargestNWfile, dp->d_name);
                }
            }
        } 

        //If we find a directory, do a recursive call.
        else if (S_ISDIR(statbuf.st_mode)){
            Largestfile(dirname, LargestWsize, LargestNWsize, LargestWfile, LargestNWfile, diskUsage);
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[]) {
    
    //Error Checking
    if (argc != 2){
        usage();
        return EXIT_FAILURE;
    }

    struct stat buf;
    if (stat(argv[1], &buf) < 0) {
        fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    //We have to check if the input is a directory, if it isn't, then fail.
    if ((!S_ISDIR(buf.st_mode))){
        fprintf(stderr, "Error: '%s' is not a directory.\n", argv[1]);
        return EXIT_FAILURE;
    }

    long int largestW, largestNW, totalDisk; //creation of vars that will store the size of largest writable/nonwritable files and total disk usage respectively
    char largestWfile[1000];
    char largestNWfile[1000]; //these store the filename. 
    totalDisk = 4096; //Setting initial disk usage to be 4096, since we have to consider the size of the root directory as well
    largestW = 0;
    largestNW = 0;

    Largestfile(argv[1], &largestW, &largestNW, largestWfile, largestNWfile, &totalDisk);

    printf("Largest writable file is %s and has size %ld\n", largestWfile, largestW);
    printf("Largest non-writable file is %s and has size %ld\n", largestNWfile, largestNW);
    printf("The total disk usage of %s is %ld\n", argv[1], totalDisk);
    return EXIT_SUCCESS;
}