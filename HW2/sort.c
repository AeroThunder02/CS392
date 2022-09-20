/*
Name: sort.c
Author: Maciej Kowalczyk
Date: 2/16/22
Pledge: I pledge my Honor that I have abided by the Stevens Honor System
*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "mergesort.h"

#define MAX_LINES 1024

void printusage(){
printf("Usage: ./sort [-i|-d] filename\n");
printf("-i: Specifies the file contains ints.\n");
printf("-d: Specifies the file contains doubles.\n");
printf("filename: The file to sort.\n");
}

FILE* Filecheck(char* fileInput){
    if (fileInput == NULL){
        fprintf(stderr, "Error: No input file specified.\n");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(fileInput, "r");
    if (file == NULL){
        fprintf(stderr, "Error: Cannot open '%s', %s\n", fileInput, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    return file;
}

int main(int argc, char *argv[]) {
    
    if (argc == 1){
        printusage();
        return EXIT_FAILURE;
    }

    int opt;
    int flagExists = 0;
    opterr = 0;
    while((opt = getopt(argc, argv, "id")) != -1){
        switch(opt){
            case 'i':
                if(flagExists != 0){
                    fprintf(stderr, "Too many flags specified\n");
                    return EXIT_FAILURE;
                }
                flagExists = 1;
                break;

            case 'd':
                if(flagExists != 0){
                    fprintf(stderr, "Too many flags specified\n");
                    return EXIT_FAILURE;
                }
                flagExists = 2;
                break;

            case '?':
                fprintf(stderr, "Unknown option: '%s' recieved.\n", optarg);
                printusage();
                return EXIT_FAILURE;
        }
    }

    if(argc > 3){
        fprintf(stderr, "Error: Too many files specified.\n");
        return EXIT_FAILURE;
    }

    FILE* file = Filecheck(argv[2]);
    
    /*
    OFFICE HOURS NOTES
    Note: TA said use flagExists for typecheck
    Note: remember to use free(varname) after a malloc
    Note: remember fclose(filename)
    Note: You can use sizeof(array) to set max bound easily
    Note: With only 1024 possible lines, define a max limit and malloc
            that amount of space each time. Easier than counting lines
            and reseting the file reading.
    */

    //rewind(file);
    int lines = 1;
    char scanner;
    while((scanner = fgetc(file)) != EOF){
        if(scanner == '\n'){
            lines++;
        }
    }
    //
    //printf("%d\n", lines); debug
    rewind(file);

    if(flagExists == 1){
        int* array = (int*)malloc(lines*sizeof(int));
        int i = 0;
        while(fscanf(file, "%d", &array[i]) == 1){
            //printf("%d\n", array[i]); debugging
            i++;
        }
        int (*compType)(const void* a, const void* b) = &int_cmp;
        mergesort(array, sizeof(array), sizeof(int), compType);
        
        for(int j = 0; j < sizeof(array); j++){
            printf("%d\n", array[j]);
        }
        free(array);
    }

    else if(flagExists == 2){
        double* array = (double*)malloc(lines*sizeof(double));
        int i = 0;
        while(fscanf(file, "%lf", &array[i]) == 1){
            i++;
        }
        int (*compType)(const void* a, const void* b) = &dbl_cmp;
        mergesort(array, sizeof(array), sizeof(double), compType);
        
        for(int j = 0; j < sizeof(array); j++){
            printf("%lf\n", array[j]);
        }
        free(array);
    }
    else{
        fprintf(stderr, "Error: Unsupported type.\n");
    }

    
    fclose(file);

   
    
    return 0;
}
