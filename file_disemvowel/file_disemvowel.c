#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#define BUF_SIZE 1024

bool is_vowel(char b) {
	if (b == 'a' ||b == 'e' ||b  == 'i' ||b == 'o' ||b == 'u'
			|| b == 'A' || b == 'E' ||b == 'I' || b == 'O' || b =='U') {
	return true;
	}
	else {
	return false;
	}
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
//	char * inBuf = (char*) calloc(BUF_SIZE, sizeof(char));
//	char * outBuf = (char*) calloc(BUF_SIZE, sizeof(char));
	char inBuf[BUF_SIZE];
	char outBuf[BUF_SIZE];
	while(!feof(inputFile)){
		fread(&inBuf, sizeof(inBuf), 1, inputFile);
		int consonant_count = 0;
		for (int i=0; i<BUF_SIZE; i++){
			if(!is_vowel(inBuf[i])) {
				consonant_count++; 
			}
		}	


		int j = 0;
		for(int i=0; i<BUF_SIZE; i++) {
			if(!is_vowel(inBuf[i])){
				outBuf[j] = inBuf[i];
				j++;
			}
		}

		fwrite(&outBuf, sizeof(outBuf), 1, outputFile);
	}
}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

	if(argc==2){
		inputFile = fopen(argv[1], "r");
	}

	if(argc == 3){
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	}
    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0;
}
