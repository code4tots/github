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



int main(int argc, char* argv[]){
	if (argc < 2){
		loadProgramFromFile("codelish.c");
	} else {
		printf("usage: %s [program file]\n", argv[0]);
	}	
	return 0;
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

