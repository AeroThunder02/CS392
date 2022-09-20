#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    FILE *input, *output;
    
    //error checking: usage and file opening
    if (argc != 3){
        fprintf(stderr, "Usage: ./text2bin <input filename> <output filename>");
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL){
        printf("%s", "Input file cannot be opened.");
        return 1;
    }
    output = fopen(argv[2], "w");
    if (output == NULL){
        printf("%s", "Output file cannot be opened.");
        return 1;
    }
    
    //reading and writing to files
    char line[50];
    while (fgets(line, sizeof(line), input)){
        int user_id, item_id, rating;
        unsigned long timestamp;
        sscanf(line, "%d %d %d %ld", &user_id, &item_id, &rating, &timestamp); //parse each line and set the 4 individual ints to their respective variables
        fwrite(&user_id, 4, 1, output); //writing
        fwrite(&item_id, 2, 1, output);
        fwrite(&rating, 1, 1, output);
        fwrite(&timestamp, 8, 1, output);   
    }
    fclose(input);
    fclose(output);
    return 0;

}