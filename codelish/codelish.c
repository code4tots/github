/*
codelish.c
*/
#include<stdio.h>
#include<stdlib.h>
// Load program text from file.
char* program;
size_t programsize;
size_t programcapacity;
void loadProgramFromFile(const char* filename);
// tokenize (char* program)
char** programtokens;
size_t* programtokensizes;
size_t numberofprogramtokens;
void tokenizeFromCharPtr(char* program);

int main(int argc, char* argv[]){
	if (argc < 2){
		loadProgramFromFile("codelish.c");
	} else {
		printf("usage: %s [program file]\n", argv[0]);
	}
	return 0;
}
// tokenize (char* program)
void tokenizeFromCharPtr(char* program){
	// Tokenize into
	// 		alphanumeric (start with letter),
	//		integral,
	//		decimal,
	//		period.
	size_t pos = 0;
	size_t ahead = 0;
	while(pos < programsize){
		
	}
}

// Load program text from file.
void loadProgramFromFile(const char* filename){
	FILE* fin = fopen(filename, "r");
	
	programcapacity = 0;
	programsize = 0;
	program = NULL;
	
	size_t increment = 1024;
	while (increment == 1024){
		programcapacity += 1024;
		program = realloc(program, programcapacity);
		
		increment = fread(program, 1, 1024, fin);
		programsize += increment;
	}
}

