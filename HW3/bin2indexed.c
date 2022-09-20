#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    FILE *input, *output, *item;
    
    //error checking: usage and file opening
    if (argc != 4){
        fprintf(stderr, "Usage: ./text2bin <binary file> <item file> <output filename>");
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL){
        printf("%s", "Input file cannot be opened.");
        return 1;
    }
    item = fopen(argv[2], "r");
    if (item == NULL){
        printf("%s", "Item file cannot be opened.");
        return 1;
    }
    output = fopen(argv[3], "w");
    if (output == NULL){
        printf("%s", "Output file cannot be opened.");
        return 1;
    }

    //really stupid, since we will be traversing the entire file multiple times and the program will be very slow, but its the easy way out 
    //first count the lines
    int lines = 1;
    char scanner;
    while((scanner = fgetc(item)) != EOF){
        if(scanner == '\n'){
            lines++;
        }
    }
    rewind(item);
    
    
    //then malloc
    unsigned long int* arr = (unsigned long int*)malloc(lines * sizeof(unsigned long int));
    int i = 0;
    
    //now get the offset of all the movies and pump em into arr
    char line[1000];
    while (fgets(line, sizeof(line), item)){
        unsigned long int offset = ftell(item);
        arr[i] = offset;
        i++;
    }

    //printf("%ld\n", arr[1681]);


    
    //now update the item_id to be the offset
    #pragma pack(1) //stops from padding struct length
    struct original {
        unsigned int uid;
        unsigned short iid;
        unsigned char rating;
        unsigned long timestamp;
    } org;

    while (fread(&org, sizeof(org), 1, input) == 1) {
        fwrite(&org.uid, 4, 1, output);
        unsigned long off = arr[org.iid]; 
        fwrite(&off, 8, 1, output);
        fwrite(&org.rating, 1, 1, output); 
        fwrite(&org.timestamp, 8, 1, output);
    }
    fclose(output);
    fclose(input);
    fclose(item);
    free(arr);
    

    return 0;
}
    