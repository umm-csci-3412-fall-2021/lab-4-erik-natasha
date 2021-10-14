#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#define BUF_SIZE 1024

// Check whether the character b is a vowel or the null character, return true if it is
bool is_vowel(char b) {
	if (b == 'a' ||b == 'e' ||b  == 'i' ||b == 'o' ||b == 'u'
			|| b == 'A' || b == 'E' ||b == 'I' || b == 'O' || b =='U' || b=='\0') {
	return true;
	}
	else {
	return false;
	}
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
	
	// While the end of the file hasn't been reached...
	while(!feof(inputFile)){

		// Allocate a buffer of BUF_SIZE characters and read that many chars from the input file
		char * inBuf = (char*) calloc(BUF_SIZE, sizeof(char));

		fread(inBuf, sizeof(char), BUF_SIZE, inputFile);
	
		// Count the number of consonants in this section of the file	
		int consonant_count = 0;
		for (int i=0; i<BUF_SIZE; i++){
			if(!is_vowel(inBuf[i])) {
				consonant_count++; 
			}
		}	

		// Allocate a buffer of appropriate size
		char * outBuf = (char*) calloc(consonant_count, sizeof(char));

		// Add all non-vowels to our output buffer
		int j = 0;
		for(int i=0; i<BUF_SIZE; i++) {
			if(!is_vowel(inBuf[i])){
				outBuf[j] = inBuf[i];
				j++;
			}
		}

		// Write the output buffer to the output file
		fwrite(outBuf, sizeof(char), consonant_count, outputFile);
	
		// Free both of the buffers so that there aren't any leaks between loops	
		free(inBuf);
		free(outBuf);
	}
}

int main(int argc, char *argv[]) {
	// This sets these to `stdin` and `stdout` by default.
	FILE *inputFile = stdin;
	FILE *outputFile = stdout;

	// If arguments are given, use the first as the input file and the second as the output file
	if(argc==2){
		inputFile = fopen(argv[1], "r");
	}

	if(argc == 3){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	}

	disemvowel(inputFile, outputFile);

	return 0;
}
