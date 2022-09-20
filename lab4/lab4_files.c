#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This program reads from an input ASCII file with 4 columns of long integers

// It first opens a file named according to the second argument and writes
// the column of the input specified by column_index to that file.
// Only one number is written per line in ASCII format

// Then, it counts the number of lines in the input file and writes the last 
// third of the input file to the second output file, also in ASCII format

// USAGE: lab4_files input_file output_file1 output_file2 column_index

int main (int argc, char **argv) {
	if (argc != 5) {
		fprintf(stderr, "Wrong number of command-line arguments\n");
		usage(argv[0]);
		return -1;
	}
	
	// TODO: complete the file opening code below
	
	FILE* in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("%s", "The input file cannot be opened!");
		exit(-1);
	}
	


	FILE* out = fopen(argv[2], "w");
	if (out == NULL) {
		printf("%s", "The output file cannot be written to/opened!");
		exit(-1);
	}
	
	

	// TODO: read all lines from the file, write the column the user 
	// selected to the first output file
	char line[200] = "";
	while(fgets(line, 200, in)){ 
		long num1, num2, num3, num4;
		if argv[4] == 0
			fscanf(in, "%ld, %*ld, %*ld, %*ld \n", num1, num2, num3, num4);
			fprintf(out, "%ld \n", num1);
		else if argv[4] == 1
			fscanf(in, "%*ld, %ld, %*ld, %*ld \n", num1, num2, num3, num4);
			fprintf(out, "%ld \n", num2);
		else if argv[4] == 2
			fscanf(in, "%*ld, %*ld, %ld, %*ld \n", num1, num2, num3, num4);
			fprintf(out, "%ld \n", num3);
		else if argv[4] == 3
			fscanf(in, "%*ld, %*ld, %*ld, %ld \n", num1, num2, num3, num4);
			fprintf(out, "%ld \n", num4);

	}
	fclose(in);
	fclose(out);

	// TODO: figure out the number of lines in the file and write the last 
	// third of the file to the second output file starting from index
	// num_lines*2/3 to the end

	return 0;
}

