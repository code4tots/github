#include<stdio.h>
#include<limits.h>

// Large integer.
typedef struct IntStruct Int;
struct IntStruct{
	unsigned int* content;
	size_t size;
}
Int* makeInt(){
	Int* ret = malloc(sizeof(Int));
	ret->content = malloc(sizeof(unsigned int));
	ret->size = 1;
}
Int* makeIntFromint(int i){
	
}


int main(int argc, char* argv[]){
}
