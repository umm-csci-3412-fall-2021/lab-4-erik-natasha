#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#define BUF_SIZE 1024

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
//	char * inBuf = (char*) calloc(BUF_SIZE, sizeof(char));
//	char * outBuf = (char*) calloc(BUF_SIZE, sizeof(char));
//	char inBuf[BUF_SIZE];
//	char outBuf[BUF_SIZE];
	while(!feof(inputFile)){
//	while(fread(inBuf, sizeof(inBuf), 1, inputFile)==1){
		char * inBuf = (char*) calloc(BUF_SIZE, sizeof(char));

//		char * outBuf = (char*) calloc(BUF_SIZE, sizeof(char));

		fread(inBuf, sizeof(char), BUF_SIZE, inputFile);
		int consonant_count = 0;
		for (int i=0; i<BUF_SIZE; i++){
			if(!is_vowel(inBuf[i])) {
				consonant_count++; 
			}
		}	

		char * outBuf = (char*) calloc(consonant_count, sizeof(char));

		int j = 0;
		for(int i=0; i<BUF_SIZE; i++) {
			if(!is_vowel(inBuf[i])){
				outBuf[j] = inBuf[i];
				j++;
			}
		}

		fwrite(outBuf, sizeof(char), consonant_count, outputFile);
//		printf("\n END OF LOOP \n");
		free(inBuf);
		free(outBuf);
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
