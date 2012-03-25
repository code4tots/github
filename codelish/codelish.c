/*
codelish.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Load program text from file.
char* program;
size_t programsize;
size_t programcapacity;
void loadProgramFromFile(const char* filename);
// Tokenize into "words"
char** programtokens;
size_t* programtokensizes;
size_t numberofprogramtokens;
void tokenizeProgramFromCharPtr(char* program);
// main
int main(int argc, char* argv[]){
	if (argc < 2){
		printf("usage: %s [program file]\n", argv[0]);
	} else {
		loadProgramFromFile(argv[1]);
        
        FILE* fout = fopen("sample.txt","w");
        fwrite(program, programsize, 1, fout);
        fclose(fout);
        
        tokenizeProgramFromCharPtr(program);
	}
	return 0;
}
// Tokenize into "words"
void tokenizeProgramFromCharPtr(char* localprogram){
    char* pch;
    // the delimiters that are chosen are the ones
    // that isspace considers to be whitespace:
    // http://www.cplusplus.com/reference/clibrary/cctype/isspace/
    pch = strtok(localprogram, " \t\n\v\f\r");
    
    while(pch != NULL){
        printf("%s\n", pch);
        pch = strtok(NULL, " \t\n\v\f\r");
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
		
		increment = fread(program + programsize, 1, 1024, fin);
		programsize += increment;
	}
}

